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
 * File:   reusable_resource.cpp
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 * 
 * Created on May 16, 2017, 9:45 AM
 */

#include "reusable_resource.h"
#include "utils.h"

namespace cg {

    reusable_resource::reusable_resource(cg::causal_graph& g) : smart_type(g, g, REUSABLE_RESOURCE_NAME) {
        fields.insert({REUSABLE_RESOURCE_CAPACITY, new ratio::field(g.get_type("real"), REUSABLE_RESOURCE_CAPACITY)});
        constructors.push_back(new reusable_resource_constructor(*this));
        predicates.insert({REUSABLE_RESOURCE_USE_PREDICATE_NAME, new use_predicate(*this)});
    }

    reusable_resource::~reusable_resource() { }

    std::vector<flaw*> reusable_resource::get_flaws() {
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

            for (const auto& rr : instances) {
                // for each pulse, the atoms starting at that pulse..
                std::map<double, std::set < ratio::atom*>> starting_atoms;
                // for each pulse, the atoms ending at that pulse..
                std::map<double, std::set < ratio::atom*>> ending_atoms;
                // all the pulses of the timeline..
                std::set<double> pulses;
                // the resource capacity..
                ratio::arith_expr capacity = rr.first->get(REUSABLE_RESOURCE_CAPACITY);

                for (const auto& a : rr.second) {
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
                    smt::lin resource_usage;
                    for (const auto& a : overlapping_atoms) {
                        ratio::arith_expr amount = a->get(REUSABLE_RESOURCE_USE_AMOUNT_NAME);
                        resource_usage += amount->l;
                    }
                    if (_solver.la.value(resource_usage) > _solver.la.value(capacity->l)) {
                        // we have a peak..
                        flaws.push_back(new reusable_resource_flaw(g, overlapping_atoms));
                    }
                }
            }

            to_check.clear();
            return flaws;
        }
    }

    void reusable_resource::new_predicate(ratio::predicate& p) {
        throw std::logic_error("it is not possible to define predicates on a reusable resource..");
    }

    bool reusable_resource::new_fact(ratio::atom& a) {
        // we apply interval-predicate if the fact becomes active..
        set_var(_solver.set.allows(a.state, *ratio::atom::active));
        if (!static_cast<ratio::predicate&> (_solver.get_predicate("IntervalPredicate")).apply_rule(a)) {
            return false;
        }
        restore_var();

        // reusable resource facts cannot unify..
        if (!_solver.sat.new_clause({smt::lit(_solver.set.allows(a.state, *ratio::atom::unified), false)})) {
            return false;
        }

        atoms.push_back({&a, new reusable_resource_atom_listener(*this, a)});
        ratio::enum_expr c_scope = a.get("scope");
        for (const auto& val : _solver.set.value(c_scope->ev)) {
            to_check.insert(static_cast<ratio::item*> (val));
        }
        return true;
    }

    bool reusable_resource::new_goal(ratio::atom& a) {
        throw std::logic_error("it is not possible to define goals on a reusable resource..");
    }

    reusable_resource::use_predicate::use_predicate(reusable_resource& rr) : ratio::predicate(rr._solver, rr, REUSABLE_RESOURCE_USE_PREDICATE_NAME,{new ratio::field(rr.g.get_type("real"), REUSABLE_RESOURCE_USE_AMOUNT_NAME)}) {
        supertypes.push_back(&rr._solver.get_predicate("IntervalPredicate"));
    }

    reusable_resource::use_predicate::~use_predicate() { }

    bool reusable_resource::use_predicate::apply_rule(ratio::atom& a) const {
        return true;
    }

    reusable_resource::reusable_resource_atom_listener::reusable_resource_atom_listener(reusable_resource& rr, ratio::atom& a) : atom_listener(a), rr(rr) { }

    reusable_resource::reusable_resource_atom_listener::~reusable_resource_atom_listener() { }

    void reusable_resource::reusable_resource_atom_listener::something_changed() {
        ratio::enum_expr c_scope = a.get("scope");
        for (const auto& val : a.get_solver().set.value(c_scope->ev)) {
            rr.to_check.insert(static_cast<ratio::item*> (val));
        }
    }

    reusable_resource::reusable_resource_flaw::reusable_resource_flaw(causal_graph& g, const std::set<ratio::atom*>& overlapping_atoms) : flaw(g), overlapping_atoms(overlapping_atoms) { }

    reusable_resource::reusable_resource_flaw::~reusable_resource_flaw() { }

    std::string reusable_resource::reusable_resource_flaw::get_label() const {
        return "rr-flaw";
    }

    void reusable_resource::reusable_resource_flaw::compute_resolvers() {
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

    reusable_resource::rr_resolver::rr_resolver(causal_graph& g, const smt::lin& cost, reusable_resource_flaw& f, const smt::lit& to_do) : resolver(g, cost, f), to_do(to_do) { }

    reusable_resource::rr_resolver::~rr_resolver() { }

    bool reusable_resource::rr_resolver::apply() {
        return g.sat.new_clause({smt::lit(chosen, false), to_do});
    }

    reusable_resource::order_resolver::order_resolver(causal_graph& g, const smt::lin& cost, reusable_resource_flaw& f, const ratio::atom& before, const ratio::atom& after, const smt::lit& to_do) : rr_resolver(g, cost, f, to_do), before(before), after(after) { }

    reusable_resource::order_resolver::~order_resolver() { }

    std::string reusable_resource::order_resolver::get_label() const {
        return "e" + std::to_string(before.state) + " <= e" + std::to_string(after.state);
    }

    reusable_resource::displace_resolver::displace_resolver(causal_graph& g, const smt::lin& cost, reusable_resource_flaw& f, const ratio::atom& a, const ratio::item& i, const smt::lit& to_do) : rr_resolver(g, cost, f, to_do), a(a), i(i) { }

    reusable_resource::displace_resolver::~displace_resolver() { }

    std::string reusable_resource::displace_resolver::get_label() const {
        ratio::enum_expr scp = a.get("scope");
        return "e" + std::to_string(scp->ev) + " != " + std::to_string(reinterpret_cast<uintptr_t> (&i));
    }
}