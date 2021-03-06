/*
 * Copyright (C) 2017 Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* 
 * File:   causal_graph.cpp
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 * 
 * Created on April 14, 2017, 10:22 AM
 */

#include "causal_graph.h"
#include "enum_flaw.h"
#include "atom_flaw.h"
#include "disjunction_flaw.h"
#include "resolver.h"
#include "smart_type.h"
#include "state_variable.h"
#include "reusable_resource.h"
#include "propositional_state.h"
#include "propositional_agent.h"
#ifndef N_CAUSAL_GRAPH_LISTENERS
#include "causal_graph_listener.h"
#endif

namespace cg {

    causal_graph::causal_graph() {
        bool r = read(std::vector<std::string>({"init.rddl"}));
        assert(r);
        types.insert({STATE_VARIABLE_NAME, new state_variable(*this)});
        types.insert({REUSABLE_RESOURCE_NAME, new reusable_resource(*this)});
        types.insert({PROPOSITIONAL_STATE_NAME, new propositional_state(*this)});
        types.insert({PROPOSITIONAL_AGENT_NAME, new propositional_agent(*this)});
#ifndef NDEBUG
        delete_file();
#endif
    }

    causal_graph::~causal_graph() {
        for (const auto& f : in_plan) {
            delete f.second;
        }
    }

    ratio::expr causal_graph::new_enum(const ratio::type& t, const std::unordered_set<ratio::item*>& allowed_vals) {
        assert(!allowed_vals.empty());
        ratio::enum_expr c_e = ratio::solver::new_enum(t, allowed_vals);
        if (allowed_vals.size() > 1) {
            enum_flaw* ef = new enum_flaw(*this, *c_e);
            new_flaw(*ef);
        }
        return c_e;
    }

    bool causal_graph::solve() {
main_loop:
        res = nullptr;
#ifndef NDEBUG
        write_file();
#endif

        // we build the planning graph..
        if (!build()) {
            // the problem is unsolvable..
            return false;
        }

        // we create a new graph var..
        graph_var = sat.new_var();
        // we use the current graph var to allow search within the current graph..
        bool a_gv = sat.assume(smt::lit(graph_var, true));
        assert(a_gv);

        // this is the next flaw to be solved..
        flaw* f_next = select_flaw();
        while (f_next) {
            assert(f_next->cost < std::numeric_limits<double>::infinity());
            if (f_next->has_subgoals()) {
                // we run out of inconsistencies, thus, we renew them..
                if (has_inconsistencies()) {
                    // we go back to root level..
                    while (!sat.root_level()) {
                        sat.pop();
                    }
                    goto main_loop;
                }
            }

            // this is the next resolver to be chosen..
            resolver& r_next = select_resolver(*f_next);
            res = &r_next;
            if (f_next->has_subgoals()) {
                resolvers.push_back(&r_next);
            }

            // we apply the resolver..
            if (!sat.assume(smt::lit(r_next.chosen, true)) || !sat.check()) {
                return false;
            }
#ifndef NDEBUG
            write_file();
#endif

            while (!has_solution()) {
                // we search within the graph..
                std::vector<smt::lit> look_elsewhere;
                for (std::vector<layer>::reverse_iterator trail_it = trail.rbegin(); trail_it != trail.rend(); ++trail_it) {
                    if (trail_it->r) {
                        look_elsewhere.push_back(smt::lit(trail_it->r->chosen, false));
                    }
                }
                look_elsewhere.push_back(smt::lit(graph_var, false));
                while (sat.value(look_elsewhere[0].v) != smt::Undefined) {
                    // we backtrack..
                    sat.pop();
                }
                if (sat.root_level()) {
                    // we have exhausted the search within the graph: we extend the graph..
                    if (!add_layer()) {
                        return false;
                    }

                    // we create a new graph var..
                    graph_var = sat.new_var();
                    // we use the current graph var to allow search within the current graph..
                    a_gv = sat.assume(smt::lit(graph_var, true));
                    assert(a_gv);
                } else {
                    record(look_elsewhere);
                    if (!sat.check()) {
                        return false;
                    }
                }
            }

            // we select a new flaw..
            f_next = select_flaw();
        }

        // we run out of flaws, we check for inconsistencies one last time..
        if (has_inconsistencies()) {
            // we go back to root level..
            while (!sat.root_level()) {
                sat.pop();
            }
            goto main_loop;
        }

        // we have found a solution..
        return true;
    }

    bool causal_graph::new_fact(ratio::atom& a) {
        atom_flaw* af = new atom_flaw(*this, a, true);
        reason.insert({&a, af});
        new_flaw(*af);
        return ratio::solver::new_fact(a);
    }

    bool causal_graph::new_goal(ratio::atom& a) {
        atom_flaw* af = new atom_flaw(*this, a, false);
        reason.insert({&a, af});
        new_flaw(*af);
        return ratio::solver::new_goal(a);
    }

    void causal_graph::new_disjunction(ratio::context& e, ratio::disjunction& d) {
        disjunction_flaw* df = new disjunction_flaw(*this, e, d);
        new_flaw(*df);
    }

    void causal_graph::new_flaw(flaw& f) {
        f.init();
        flaw_q.push(&f);
        if (sat.value(f.in_plan) == smt::True) {
            // we have a top-level (landmark) flaw..
            flaws.insert(&f);
        } else {
            // we listen for the flaw to become in_plan..
            in_plan.insert({f.in_plan, &f});
            bind(f.in_plan);
        }
#ifndef N_CAUSAL_GRAPH_LISTENERS
        for (const auto& l : listeners) {
            l->new_flaw(f);
        }
#endif
    }

    void causal_graph::new_resolver(resolver& r) {
#ifndef N_CAUSAL_GRAPH_LISTENERS
        for (const auto& l : listeners) {
            l->new_resolver(r);
        }
#endif
    }

    void causal_graph::new_causal_link(flaw& f, resolver& r) {
        r.preconditions.push_back(&f);
        f.supports.push_back(&r);
        bool new_clause = sat.new_clause({smt::lit(r.chosen, false), smt::lit(f.in_plan, true)});
        assert(new_clause);
#ifndef N_CAUSAL_GRAPH_LISTENERS
        for (const auto& l : listeners) {
            l->causal_link_added(f, r);
        }
#endif
    }

    bool causal_graph::propagate(const smt::lit& p, std::vector<smt::lit>& cnfl) {
        assert(cnfl.empty());
        if (in_plan.find(p.v) != in_plan.end()) {
            // a decision has been taken about the presence of this flaw within the current partial solution..
            flaw* f = in_plan.at(p.v);
            if (p.sign) {
                // a flaw has been added to the current partial solution..
                flaws.insert(f);
                if (!trail.empty()) {
                    trail.back().new_flaws.insert(f);
                }
            } else {
                // a flaw has been removed from the current partial solution..
                set_cost(*f, std::numeric_limits<double>::infinity());
            }
#ifndef N_CAUSAL_GRAPH_LISTENERS
            for (const auto& l : listeners) {
                l->flaw_state_changed(*f);
            }
#endif
        } else {
            flaw_costs_q.push(&chosen.at(p.v)->effect);
            propagate_costs();
        }

        if (flaw_q.empty()) {
            // we can use standard search techniques..
            if (!has_solution()) {
                // we have made the heuristic blind..
                cnfl.push_back(p);
                for (std::vector<layer>::reverse_iterator trail_it = trail.rbegin(); trail_it != trail.rend(); ++trail_it) {
                    if (trail_it->r) {
                        // this resolver is null if we are calling the check from the sat core! Not bad: shorter conflict..
                        cnfl.push_back(smt::lit(trail_it->r->chosen, false));
                    }
                }
                return false;
            }
        }

        return true;
    }

    bool causal_graph::check(std::vector<smt::lit>& cnfl) {
        assert(cnfl.empty());
        return true;
    }

    void causal_graph::push() {
        trail.push_back(layer(res));
        if (res) {
            trail.back().solved_flaws.insert(&res->effect);
            flaws.erase(&res->effect);
        }
    }

    void causal_graph::pop() {
        // we erase new flaws..
        for (const auto& f : trail.back().new_flaws) {
            flaws.erase(f);
        }
        // we reintroduce the solved flaw..
        for (const auto& f : trail.back().solved_flaws) {
            flaws.insert(f);
        }
        // we restore flaw costs..
        for (const auto& c : trail.back().old_costs) {
            c.first->cost = c.second;
        }
#ifndef N_CAUSAL_GRAPH_LISTENERS
        for (const auto& c : trail.back().old_costs) {
            for (const auto& l : listeners) {
                l->flaw_cost_changed(*c.first);
            }
        }
#endif
        // we manage structural flaws..
        if (!resolvers.empty() && resolvers.back() == trail.back().r) {
            resolvers.pop_back();
        }
        trail.pop_back();
    }

    bool causal_graph::build() {
        assert(sat.root_level());
        if (flaw_q.empty()) {
            // there is nothing to reason on..
            return true;
        }

        while (!has_solution() && !flaw_q.empty()) {
            assert(flaw_q.front()->initialized);
            assert(!flaw_q.front()->expanded);
            if (is_deferrable(*flaw_q.front())) {
                // we postpone the expansion..
                flaw_q.push(flaw_q.front());
            } else {
                if (!flaw_q.front()->expand() || !sat.check()) {
                    return false;
                }

                for (const auto& r : flaw_q.front()->resolvers) {
                    resolvers.push_front(r);
                    set_var(r->chosen);
                    if (!r->apply() || !sat.check()) {
                        return false;
                    }
#ifndef NDEBUG
                    write_file();
#endif
                    restore_var();
                    if (r->preconditions.empty()) {
                        // there are no requirements for this resolver..
                        set_cost(*flaw_q.front(), std::min(flaw_q.front()->cost, la.value(r->cost)));
                        // making this resolver false might make the heuristic blind..
                        chosen.insert({r->chosen, r});
                        bind(r->chosen);
                    }
                    resolvers.pop_front();
                }
            }
            flaw_q.pop();
        }

        return true;
    }

    bool causal_graph::add_layer() {
        assert(sat.root_level());

        std::vector<flaw*> fs;
        while (!flaw_q.empty()) {
            fs.push_back(flaw_q.front());
            flaw_q.pop();
        }

        for (const auto& f : fs) {
            assert(f->initialized);
            assert(!f->expanded);
            if (!f->expand() || !sat.check()) {
                return false;
            }

            for (const auto& r : f->resolvers) {
                resolvers.push_front(r);
                set_var(r->chosen);
                if (!r->apply() || !sat.check()) {
                    return false;
                }
#ifndef NDEBUG
                write_file();
#endif
                restore_var();
                if (r->preconditions.empty()) {
                    // there are no requirements for this resolver..
                    set_cost(*f, std::min(f->cost, la.value(r->cost)));
                    // making this resolver false might make the heuristic blind..
                    chosen.insert({r->chosen, r});
                    bind(r->chosen);
                }
                resolvers.pop_front();
            }
        }

        return true;
    }

    bool causal_graph::has_solution() {
        for (const auto& f : flaws) {
            if (f->cost == std::numeric_limits<double>::infinity()) {
                return false;
            }
        }
        return true;
    }

    bool causal_graph::is_deferrable(flaw& f) {
        std::queue<flaw*> q;
        q.push(&f);
        while (!q.empty()) {
            if (!q.front()->exclusive) {
                // we cannot defer this flaw..
                return false;
            } else if (sat.value(q.front()->in_plan) == smt::False) {
                // it is not possible to solve this flaw with current assignments.. thus we defer..
                return true;
            } else if (q.front()->cost < std::numeric_limits<double>::infinity()) {
                // we already have a possible solution for this flaw.. thus we defer..
                return true;
            }
            for (const auto& r : q.front()->causes) {
                q.push(&r->effect);
            }
            q.pop();
        }
        // we cannot defer this flaw..
        return false;
    }

    flaw* causal_graph::select_flaw() {
        // this is the next flaw to be solved (i.e., the most expensive one)..
        flaw* f_next = nullptr;
        for (auto it = flaws.begin(); it != flaws.end();) {
            assert((*it)->expanded);
            assert(sat.value((*it)->in_plan) == smt::True);
            if (std::count_if((*it)->resolvers.begin(), (*it)->resolvers.end(), [&](resolver * r) {
                    return sat.value(r->chosen) != smt::False;
                }) == 1) {
            assert(sat.value((*std::find_if((*it)->resolvers.begin(), (*it)->resolvers.end(), [&](resolver * r) {
                return sat.value(r->chosen) != smt::False;
            }))->chosen) == smt::True);
            // we have a trivial flaw..
            if (!trail.empty()) {
                trail.back().solved_flaws.insert((*it));
            }
            flaws.erase(it++);
        } else {
                if (!f_next) {
                    f_next = *it;
                } else if (f_next->has_subgoals() && !(*it)->has_subgoals()) {
                    // we prefere non-structural flaws (i.e., inconsistencies) to structural ones..
                    f_next = *it;
                } else if (f_next->has_subgoals() == (*it)->has_subgoals() && f_next->cost < (*it)->cost) {
                    f_next = *it;
                }
                ++it;
            }
        }
#ifndef N_CAUSAL_GRAPH_LISTENERS
        if (f_next) {
            for (const auto& l : listeners) {
                l->current_flaw(*f_next);
            }
        }
#endif
        return f_next;
    }

    resolver& causal_graph::select_resolver(flaw& f) {
        double r_cost = std::numeric_limits<double>::infinity();
        resolver* r_next; // this is the next resolver to be chosen (i.e., the cheapest one)..
        for (const auto& r : f.resolvers) {
            double c_cost = r->get_cost();
            if (c_cost < r_cost) {
                r_cost = c_cost;
                r_next = r;
            }
        }
#ifndef N_CAUSAL_GRAPH_LISTENERS
        for (const auto& l : listeners) {
            l->current_resolver(*r_next);
        }
#endif
        return *r_next;
    }

    void causal_graph::set_cost(flaw& f, double cost) {
        if (f.cost != cost) {
            if (!trail.empty()) {
                trail.back().old_costs.insert({&f, f.cost});
            }
            f.cost = cost;
#ifndef N_CAUSAL_GRAPH_LISTENERS
            for (const auto& l : listeners) {
                l->flaw_cost_changed(f);
            }
#endif

            for (const auto& supp : f.supports) {
                flaw_costs_q.push(&supp->effect);
            }
            propagate_costs();
        }
    }

    void causal_graph::propagate_costs() {
        while (!flaw_costs_q.empty()) {
            double f_cost = std::numeric_limits<double>::infinity();
            for (const auto& r : flaw_costs_q.front()->resolvers) {
                double c = r->get_cost();
                if (c < f_cost) {
                    f_cost = c;
                }
            }
            if (flaw_costs_q.front()->cost != f_cost) {
                if (!trail.empty()) {
                    trail.back().old_costs.insert({flaw_costs_q.front(), flaw_costs_q.front()->cost});
                }
                flaw_costs_q.front()->cost = f_cost;
#ifndef N_CAUSAL_GRAPH_LISTENERS
                for (const auto& l : listeners) {
                    l->flaw_cost_changed(*flaw_costs_q.front());
                }
#endif
                for (const auto& supp : flaw_costs_q.front()->supports) {
                    flaw_costs_q.push(&supp->effect);
                }
            }
            flaw_costs_q.pop();
        }
    }

    bool causal_graph::has_inconsistencies() {
        std::vector<flaw*> incs;
        std::queue<ratio::type*> q;
        for (const auto& t : get_types()) {
            if (!t.second->primitive) {
                q.push(t.second);
            }
        }
        while (!q.empty()) {
            if (smart_type * st = dynamic_cast<smart_type*> (q.front())) {
                std::vector<flaw*> c_incs = st->get_flaws();
                incs.insert(incs.end(), c_incs.begin(), c_incs.end());
            }
            for (const auto& st : q.front()->get_types()) {
                q.push(st.second);
            }
            q.pop();
        }

        // we initialize the new flaws..
        for (const auto& f : incs) {
            new_flaw(*f);
        }

        return !incs.empty();
    }
}