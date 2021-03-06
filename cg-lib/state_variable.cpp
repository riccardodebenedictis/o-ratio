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
 * File:   state_variable.cpp
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 * 
 * Created on April 21, 2017, 2:08 PM
 */

#include "state_variable.h"
#include "predicate.h"
#include "utils.h"

namespace cg {

    state_variable::state_variable(cg::causal_graph& g) : smart_type(g, g, STATE_VARIABLE_NAME) {
        constructors.push_back(new sv_constructor(*this));
    }

    state_variable::~state_variable() {
        // we clear the atom listeners..
        for (const auto& a : atoms) {
            delete a.second;
        }
    }

    std::vector<flaw*> state_variable::get_flaws() {
        std::vector<flaw*> flaws;
        if (to_check.empty()) {
            // nothing has changed since last inconsistency check..
            return flaws;
        } else {
            // we collect atoms for each state variable..
            std::unordered_map<ratio::item*, std::vector < ratio::atom*>> instances;
            for (const auto& a : atoms) {
                // we filter out those which are not strictly active..
                if (_solver.sat.value(_solver.set.allows(a.first->state, *ratio::atom::active)) == smt::True) {
                    ratio::enum_expr c_scope = a.first->get("scope");
                    for (const auto& i : _solver.set.value(c_scope->ev)) {
                        if (to_check.find(static_cast<ratio::item*> (i)) != to_check.end()) {
                            instances[static_cast<ratio::item*> (i)].push_back(a.first);
                            break;
                        }
                    }
                }
            }

            for (const auto& sv : instances) {
                // for each pulse, the atoms starting at that pulse..
                std::map<double, std::set < ratio::atom*>> starting_atoms;
                // for each pulse, the atoms ending at that pulse..
                std::map<double, std::set < ratio::atom*>> ending_atoms;
                // all the pulses of the timeline..
                std::set<double> pulses;

                for (const auto& a : sv.second) {
                    ratio::arith_expr s_expr = a->get("start");
                    ratio::arith_expr e_expr = a->get("end");
                    double start = _solver.la.value(s_expr->l);
                    double end = _solver.la.value(e_expr->l);
                    starting_atoms[start].insert(a);
                    ending_atoms[end].insert(a);
                    pulses.insert(start);
                    pulses.insert(end);
                }

                std::set<ratio::atom*> overlapping_atoms;
                for (const auto& p : pulses) {
                    if (starting_atoms.find(p) != starting_atoms.end()) {
                        for (const auto& a : starting_atoms.at(p)) {
                            overlapping_atoms.insert(a);
                        }
                    }
                    if (ending_atoms.find(p) != ending_atoms.end()) {
                        for (const auto& a : ending_atoms.at(p)) {
                            overlapping_atoms.erase(a);
                        }
                    }
                    if (overlapping_atoms.size() > 1) {
                        // we have a peak..
                        flaws.push_back(new sv_flaw(g, overlapping_atoms));
                    }
                }
            }

            to_check.clear();
            return flaws;
        }
    }

    void state_variable::new_predicate(ratio::predicate& p) {
        inherit(static_cast<ratio::predicate&> (_solver.get_predicate("IntervalPredicate")), p);
    }

    bool state_variable::new_fact(ratio::atom& a) {
        // we apply interval-predicate if the fact becomes active..
        set_var(_solver.set.allows(a.state, *ratio::atom::active));
        if (!static_cast<ratio::predicate&> (_solver.get_predicate("IntervalPredicate")).apply_rule(a)) {
            return false;
        }
        restore_var();

        atoms.push_back({&a, new sv_atom_listener(*this, a)});
        ratio::enum_expr c_scope = a.get("scope");
        for (const auto& val : _solver.set.value(c_scope->ev)) {
            to_check.insert(static_cast<ratio::item*> (val));
        }
        return true;
    }

    bool state_variable::new_goal(ratio::atom& a) {
        atoms.push_back({&a, new sv_atom_listener(*this, a)});
        ratio::enum_expr c_scope = a.get("scope");
        for (const auto& val : _solver.set.value(c_scope->ev)) {
            to_check.insert(static_cast<ratio::item*> (val));
        }
        return true;
    }

    state_variable::sv_atom_listener::sv_atom_listener(state_variable& sv, ratio::atom& a) : atom_listener(a), sv(sv) { }

    state_variable::sv_atom_listener::~sv_atom_listener() { }

    void state_variable::sv_atom_listener::something_changed() {
        ratio::enum_expr c_scope = a.get("scope");
        for (const auto& val : a.get_solver().set.value(c_scope->ev)) {
            sv.to_check.insert(static_cast<ratio::item*> (val));
        }
    }

    state_variable::sv_flaw::sv_flaw(causal_graph& g, const std::set<ratio::atom*>& overlapping_atoms) : flaw(g), overlapping_atoms(overlapping_atoms) { }

    state_variable::sv_flaw::~sv_flaw() { }

    std::string state_variable::sv_flaw::get_label() const {
        return "sv-flaw";
    }

    void state_variable::sv_flaw::compute_resolvers() {
        std::vector<std::vector < ratio::atom*>> cs = smt::combinations(std::vector<ratio::atom*>(overlapping_atoms.begin(), overlapping_atoms.end()), 2);
        for (const auto& as : cs) {
            ratio::arith_expr a0_start = as[0]->get("start");
            ratio::arith_expr a0_end = as[0]->get("end");
            ratio::arith_expr a1_start = as[1]->get("start");
            ratio::arith_expr a1_end = as[1]->get("end");

            ratio::bool_expr a0_before_a1 = g.leq(a0_end, a1_start);
            if (g.sat.value(a0_before_a1->l) != smt::False) {
                add_resolver(*new order_resolver(g, smt::lin(0.0), *this, *as[0], *as[1], a0_before_a1->l));
            }
            ratio::bool_expr a1_before_a0 = g.leq(a1_end, a0_start);
            if (g.sat.value(a1_before_a0->l) != smt::False) {
                add_resolver(*new order_resolver(g, smt::lin(0.0), *this, *as[1], *as[0], a1_before_a0->l));
            }

            ratio::enum_expr a0_scope = as[0]->get("scope");
            std::unordered_set<smt::set_item*> a0_scopes = g.set.value(a0_scope->ev);
            if (a0_scopes.size() > 1) {
                for (const auto& sc : a0_scopes) {
                    add_resolver(*new displace_resolver(g, smt::lin(0.0), *this, *as[0], *static_cast<ratio::item*> (sc), smt::lit(g.set.allows(a0_scope->ev, *sc), false)));
                }
            }

            ratio::enum_expr a1_scope = as[1]->get("scope");
            std::unordered_set<smt::set_item*> a1_scopes = g.set.value(a1_scope->ev);
            if (a1_scopes.size() > 1) {
                for (const auto& sc : a1_scopes) {
                    add_resolver(*new displace_resolver(g, smt::lin(0.0), *this, *as[1], *static_cast<ratio::item*> (sc), smt::lit(g.set.allows(a1_scope->ev, *sc), false)));
                }
            }
        }
    }

    state_variable::sv_resolver::sv_resolver(causal_graph& g, const smt::lin& cost, sv_flaw& f, const smt::lit& to_do) : resolver(g, cost, f), to_do(to_do) { }

    state_variable::sv_resolver::~sv_resolver() { }

    bool state_variable::sv_resolver::apply() {
        return g.sat.new_clause({smt::lit(chosen, false), to_do});
    }

    state_variable::order_resolver::order_resolver(causal_graph& g, const smt::lin& cost, sv_flaw& f, const ratio::atom& before, const ratio::atom& after, const smt::lit& to_do) : sv_resolver(g, cost, f, to_do), before(before), after(after) { }

    state_variable::order_resolver::~order_resolver() { }

    std::string state_variable::order_resolver::get_label() const {
        return "e" + std::to_string(before.state) + " <= e" + std::to_string(after.state);
    }

    state_variable::displace_resolver::displace_resolver(causal_graph& g, const smt::lin& cost, sv_flaw& f, const ratio::atom& a, const ratio::item& i, const smt::lit& to_do) : sv_resolver(g, cost, f, to_do), a(a), i(i) { }

    state_variable::displace_resolver::~displace_resolver() { }

    std::string state_variable::displace_resolver::get_label() const {
        ratio::enum_expr scp = a.get("scope");
        return "scope (e" + std::to_string(scp->ev) + ") != " + std::to_string(reinterpret_cast<uintptr_t> (&i));
    }
}