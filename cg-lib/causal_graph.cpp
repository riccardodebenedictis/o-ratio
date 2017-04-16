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

namespace cg {

    causal_graph::causal_graph() { }

    causal_graph::~causal_graph() { }

    ratio::expr causal_graph::new_enum(const ratio::type& t, const std::unordered_set<ratio::item*>& allowed_vals) {
        assert(!allowed_vals.empty());
        ratio::enum_expr c_e = ratio::solver::new_enum(t, allowed_vals);
        if (allowed_vals.size() > 1) {
            enum_flaw* ef = new enum_flaw(*this, *c_e);
            new_flaw(*ef);
        }
        return c_e;
    }

    bool causal_graph::solve() { }

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
    }

    smt::constr* causal_graph::propagate(const smt::lit& p) {
        flaw* f = in_plan.at(p.v);
        if (p.sign) {
            flaws.insert(f);
            if (!trail.empty()) {
                trail.back().new_flaws.insert(f);
            }
        } else {
            set_cost(*f, std::numeric_limits<double>::infinity());
        }
        return nullptr;
    }

    smt::constr* causal_graph::check() {
        return nullptr;
    }

    void causal_graph::push() { }

    void causal_graph::pop() { }

    bool causal_graph::build() { }

    bool causal_graph::add_layer() { }

    bool causal_graph::has_solution() { }

    bool causal_graph::is_deferrable(flaw& f) { }

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
        return *r_next;
    }

    void causal_graph::set_cost(flaw& f, double cost) { }
}