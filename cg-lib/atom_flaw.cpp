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
 * File:   atom_flaw.cpp
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 * 
 * Created on April 14, 2017, 2:28 PM
 */

#include "atom_flaw.h"
#include "causal_graph.h"
#include "predicate.h"

namespace cg {

    atom_flaw::atom_flaw(causal_graph& g, ratio::atom& a, bool is_fact) : flaw(g, true), a(a), is_fact(is_fact) { }

    atom_flaw::~atom_flaw() { }

    std::string atom_flaw::get_label() const {
        if (is_fact) {
            return "fact e" + std::to_string(a.state);
        } else {
            return "goal e" + std::to_string(a.state);
        }
    }

    bool atom_flaw::compute_resolvers(std::vector<resolver*>& rs) {
        std::unordered_set<smt::set_item*> a_state = g.set.value(a.state);
        if (a_state.find(ratio::atom::unified) != a_state.end()) {
            for (const auto& i : a.t.get_instances()) {
                if (&*i == &a) {
                    continue;
                }

                ratio::atom* c_a = static_cast<ratio::atom*> (&*i);
                if (!g.reason.at(c_a)->is_expanded()) {
                    continue;
                }
                std::unordered_set<smt::set_item*> c_state = g.set.value(c_a->state);
                if (c_state.find(ratio::atom::active) == c_state.end() || !a.equates(*c_a)) {
                    continue;
                }
                // atom c_a is a good candidate for unification..
                std::vector<smt::lit> unif_lits;
                std::unordered_set<flaw*> seen;
                std::queue<flaw*> q;
                q.push(g.reason.at(&a));
                q.push(g.reason.at(c_a));
                while (!q.empty()) {
                    assert(g.sat.value(q.front()->get_in_plan()) != smt::False);
                    if (seen.find(q.front()) != seen.end()) {
                        // we do not allow cyclic causality..
                        break;
                    }
                    seen.insert(q.front());
                    if (g.sat.value(q.front()->get_in_plan()) == smt::Undefined) {
                        for (const auto& cause : q.front()->get_causes()) {
                            assert(g.sat.value(cause->get_chosen()) != smt::False);
                            unif_lits.push_back(smt::lit(cause->get_chosen(), true));
                            q.push(&cause->get_effect());
                        }
                    }
                    q.pop();
                }
                if (!q.empty()) {
                    continue;
                }
                unif_lits.push_back(smt::lit(g.set.allows(a.state, *ratio::atom::unified), true));
                unif_lits.push_back(smt::lit(g.set.allows(c_a->state, *ratio::atom::active), true));
                smt::var eq_v = a.eq(*c_a);
                if (g.sat.value(eq_v) == smt::False) {
                    continue;
                }
                unif_lits.push_back(smt::lit(a.eq(*c_a), true));
                if (g.sat.check(unif_lits)) {
                    // unification is actually possible!
                    unify_atom* u_res = new unify_atom(g, *this, a, *c_a, unif_lits);
                    rs.push_back(u_res);
                    bool add_pre = u_res->add_precondition(*g.reason.at(c_a));
                    assert(add_pre);
                    g.set_cost(*this, g.reason.at(c_a)->get_cost());
                }
            }
        }
        if (rs.empty()) {
            // we remove unification from atom state..
            bool not_unify = g.sat.new_clause({smt::lit(g.set.allows(a.state, *ratio::atom::unified), false)});
            assert(not_unify);
        }
        if (is_fact) {
            rs.push_back(new add_fact(g, *this, a));
        } else {
            rs.push_back(new expand_goal(g, *this, a));
        }
        return true;
    }

    atom_flaw::add_fact::add_fact(causal_graph& cg, atom_flaw& f, ratio::atom& a) : resolver(cg, smt::lin(0), f), a(a) { }

    atom_flaw::add_fact::~add_fact() { }

    std::string atom_flaw::add_fact::get_label() const {
        return "add fact";
    }

    bool atom_flaw::add_fact::apply() {
        return g.sat.new_clause({smt::lit(chosen, false), smt::lit(g.set.allows(a.state, *ratio::atom::active), true)});
    }

    atom_flaw::expand_goal::expand_goal(causal_graph& cg, atom_flaw& f, ratio::atom& a) : resolver(cg, smt::lin(1), f), a(a) { }

    atom_flaw::expand_goal::~expand_goal() { }

    std::string atom_flaw::expand_goal::get_label() const {
        return "expand goal";
    }

    bool atom_flaw::expand_goal::apply() {
        return g.sat.new_clause({smt::lit(chosen, false), smt::lit(g.set.allows(a.state, *ratio::atom::active), true)}) && static_cast<const ratio::predicate*> (&a.t)->apply_rule(a);
    }

    atom_flaw::unify_atom::unify_atom(causal_graph& cg, atom_flaw& f, ratio::atom& a, ratio::atom& with, const std::vector<smt::lit>& unif_lits) : resolver(cg, smt::lin(0), f), a(a), with(with), unif_lits(unif_lits) { }

    atom_flaw::unify_atom::~unify_atom() { }

    std::string atom_flaw::unify_atom::get_label() const {
        return "unify";
    }

    bool atom_flaw::unify_atom::apply() {
        for (const auto& v : unif_lits) {
            if (!g.sat.new_clause({smt::lit(chosen, false), v})) {
                return false;
            }
        }
        return true;
    }
}