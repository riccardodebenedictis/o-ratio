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
 * File:   propositional_state.cpp
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 * 
 * Created on May 17, 2017, 11:53 AM
 */

#include "propositional_state.h"
#include "predicate.h"

namespace cg {

    propositional_state::propositional_state(cg::causal_graph& g) : smart_type(g, g, PROPOSITIONAL_STATE_NAME) {
        constructors.push_back(new ps_constructor(*this));
    }

    propositional_state::~propositional_state() {
        // we clear the atom listeners..
        for (const auto& a : atoms) {
            delete a.second;
        }
    }

    std::vector<flaw*> propositional_state::get_flaws() {
        std::vector<flaw*> flaws;
        if (to_check.empty()) {
            // nothing has changed since last inconsistency check..
            return flaws;
        } else {
            return flaws;
        }
    }

    void propositional_state::new_predicate(ratio::predicate& p) {
        inherit(static_cast<ratio::predicate&> (_solver.get_predicate("IntervalPredicate")), p);
    }

    bool propositional_state::new_fact(ratio::atom& a) {
        // we apply interval-predicate if the fact becomes active..
        set_var(_solver.set.allows(a.state, *ratio::atom::active));
        if (!static_cast<ratio::predicate&> (_solver.get_predicate("IntervalPredicate")).apply_rule(a)) {
            return false;
        }
        restore_var();

        atoms.push_back({&a, new ps_atom_listener(*this, a)});
        to_check.insert(&a);
        return true;
    }

    bool propositional_state::new_goal(ratio::atom& a) {
        atoms.push_back({&a, new ps_atom_listener(*this, a)});
        to_check.insert(&a);
        return true;
    }

    propositional_state::ps_atom_listener::ps_atom_listener(propositional_state& ps, ratio::atom& a) : atom_listener(a), ps(ps) { }

    propositional_state::ps_atom_listener::~ps_atom_listener() { }

    void propositional_state::ps_atom_listener::something_changed() {
        ps.to_check.insert(&a);
    }

    propositional_state::ps_flaw::ps_flaw(causal_graph& g, const std::set<ratio::atom*>& overlapping_atoms) : flaw(g), overlapping_atoms(overlapping_atoms) { }

    propositional_state::ps_flaw::~ps_flaw() { }

    std::string propositional_state::ps_flaw::get_label() const {
        return "ps-flaw";
    }

    void propositional_state::ps_flaw::compute_resolvers() { }

    propositional_state::ps_resolver::ps_resolver(causal_graph& g, const smt::lin& cost, ps_flaw& f, const smt::lit& to_do) : resolver(g, cost, f), to_do(to_do) { }

    propositional_state::ps_resolver::~ps_resolver() { }

    bool propositional_state::ps_resolver::apply() {
        return g.sat.new_clause({smt::lit(chosen, false), to_do});
    }

    propositional_state::order_resolver::order_resolver(causal_graph& g, const smt::lin& cost, ps_flaw& f, const ratio::atom& before, const ratio::atom& after, const smt::lit& to_do) : ps_resolver(g, cost, f, to_do), before(before), after(after) { }

    propositional_state::order_resolver::~order_resolver() { }

    std::string propositional_state::order_resolver::get_label() const {
        return "e" + std::to_string(before.state) + " <= e" + std::to_string(after.state);
    }

    propositional_state::displace_resolver::displace_resolver(causal_graph& g, const smt::lin& cost, ps_flaw& f, const ratio::atom& a, const std::string& f_name, const ratio::item& i, const smt::lit& to_do) : ps_resolver(g, cost, f, to_do), a(a), f_name(f_name), i(i) { }

    propositional_state::displace_resolver::~displace_resolver() { }

    std::string propositional_state::displace_resolver::get_label() const {
        ratio::enum_expr scp = a.get(f_name);
        return f_name + " (e" + std::to_string(scp->ev) + ") != " + std::to_string(reinterpret_cast<uintptr_t> (&i));
    }
}