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

    atom_flaw::atom_flaw(causal_graph& cg, ratio::atom& a, bool is_fact) : flaw(cg, true), a(a), is_fact(is_fact) { }

    atom_flaw::~atom_flaw() { }

    bool atom_flaw::compute_resolvers(std::vector<resolver*>& rs) {
        std::unordered_set<smt::set_item*> a_state = cg.set.value(a.state);
        if (a_state.find(ratio::atom::unified) != a_state.end()) {
            for (const auto& i : a.t.get_instances()) {
                if (&*i != &a) {
                    ratio::atom* c_a = static_cast<ratio::atom*> (&*i);
                    if (cg.reason.at(c_a)->is_expanded()) {
                        std::unordered_set<smt::set_item*> c_state = cg.set.value(c_a->state);
                        if (c_state.find(ratio::atom::active) != c_state.end() && a.equates(*c_a)) {
                            // atom c_a is a good candidate for unification..
                            std::vector<smt::lit> causal_and;
                            std::unordered_set<flaw*> seen;
                            std::queue<flaw*> q;
                            q.push(cg.reason.at(&a));
                            q.push(cg.reason.at(c_a));
                            while (!q.empty()) {
                                assert(cg.sat.value(q.front()->get_in_plan()) != smt::False);
                                if (seen.find(q.front()) != seen.end()) {
                                    goto next_atom;
                                }
                                seen.insert(q.front());
                                if (cg.sat.value(q.front()->get_in_plan()) == smt::Undefined) {
                                    for (const auto& cause : q.front()->get_causes()) {
                                        assert(cg.sat.value(cause->get_chosen()) != smt::False);
                                        causal_and.push_back(smt::lit(cause->get_chosen(), true));
                                        q.push(&cause->get_effect());
                                    }
                                }
                                q.pop();
                            }
                            causal_and.push_back(smt::lit(cg.set.allows(a.state, *ratio::atom::unified), true));
                            causal_and.push_back(smt::lit(cg.set.allows(c_a->state, *ratio::atom::active), true));
                            causal_and.push_back(smt::lit(a.eq(*c_a), true));
                            smt::var unify = cg.sat.new_conj(causal_and);
                            //                            if (cg.sat.value(unify) != smt::False && cg.sat.check(smt::lit(unify, true))) {
                            //                                // unification is actually possible!
                            //                                unify_atom* u_res = new unify_atom(cg, *this, a, *c_a, unify);
                            //                                rs.push_back(u_res);
                            //                                bool add_pre = u_res->add_precondition(*cg.reason.at(c_a));
                            //                                assert(add_pre);
                            //                                cg.set_cost(*this, cg.reason.at(c_a)->get_cost());
                            //                            }
                        }
                    }
                }
next_atom:
                ;
            }
        }
        if (rs.empty()) {
            // we remove unification from atom state..
            bool not_unify = cg.sat.new_clause({smt::lit(cg.set.allows(a.state, *ratio::atom::unified), false)});
            assert(not_unify);
        }
        if (is_fact) {
            rs.push_back(new add_fact(cg, *this, a));
        } else {
            rs.push_back(new expand_goal(cg, *this, a));
        }
        return true;
    }

    atom_flaw::add_fact::add_fact(causal_graph& cg, atom_flaw& f, ratio::atom& a) : resolver(cg, smt::lin(0), f), a(a) { }

    atom_flaw::add_fact::~add_fact() { }

    bool atom_flaw::add_fact::apply() {
        return cg.sat.new_clause({smt::lit(chosen, false), smt::lit(cg.set.allows(a.state, *ratio::atom::active), true)});
    }

    atom_flaw::expand_goal::expand_goal(causal_graph& cg, atom_flaw& f, ratio::atom& a) : resolver(cg, smt::lin(1), f), a(a) { }

    atom_flaw::expand_goal::~expand_goal() { }

    bool atom_flaw::expand_goal::apply() {
        return cg.sat.new_clause({smt::lit(chosen, false), smt::lit(cg.set.allows(a.state, *ratio::atom::active), true)}) && static_cast<const ratio::predicate*> (&a.t)->apply_rule(a);
    }

    atom_flaw::unify_atom::unify_atom(causal_graph& cg, atom_flaw& f, ratio::atom& a, ratio::atom& with, smt::var unif_var) : resolver(cg, smt::lin(0), f), a(a), with(with), unif_var(unif_var) { }

    atom_flaw::unify_atom::~unify_atom() { }

    bool atom_flaw::unify_atom::apply() {
        return cg.sat.new_clause({smt::lit(chosen, false), smt::lit(unif_var, true)});
    }
}