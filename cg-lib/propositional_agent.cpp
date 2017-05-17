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
 * File:   propositional_agent.cpp
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 * 
 * Created on May 17, 2017, 12:29 PM
 */

#include "propositional_agent.h"
#include "predicate.h"

namespace cg {

    propositional_agent::propositional_agent(cg::causal_graph& g) : smart_type(g, g, PROPOSITIONAL_AGENT_NAME) {
        constructors.push_back(new agnt_constructor(*this));
    }

    propositional_agent::~propositional_agent() { }

    std::vector<flaw*> propositional_agent::get_flaws() {
        std::vector<flaw*> flaws;
        if (to_check.empty()) {
            // nothing has changed since last inconsistency check..
            return flaws;
        } else {
            return flaws;
        }
    }

    bool propositional_agent::new_fact(ratio::atom& a) {
        // we apply interval-predicate if the fact becomes active..
        set_var(_solver.set.allows(a.state, *ratio::atom::active));
        for (const auto& p : a.t.get_supertypes()) {
            if (!static_cast<ratio::predicate*> (p)->apply_rule(a)) {
                return false;
            }
        }
        restore_var();

        atoms.push_back({&a, new agnt_atom_listener(*this, a)});
        to_check.insert(&a);
        return true;
    }

    bool propositional_agent::new_goal(ratio::atom& a) {
        atoms.push_back({&a, new agnt_atom_listener(*this, a)});
        to_check.insert(&a);
        return true;
    }

    propositional_agent::agnt_atom_listener::agnt_atom_listener(propositional_agent& agnt, ratio::atom& a) : atom_listener(a), agnt(agnt) { }

    propositional_agent::agnt_atom_listener::~agnt_atom_listener() { }

    void propositional_agent::agnt_atom_listener::something_changed() {
        agnt.to_check.insert(&a);
    }

    propositional_agent::agnt_flaw::agnt_flaw(causal_graph& g, const std::set<ratio::atom*>& overlapping_atoms) : flaw(g), overlapping_atoms(overlapping_atoms) { }

    propositional_agent::agnt_flaw::~agnt_flaw() { }

    std::string propositional_agent::agnt_flaw::get_label() const {
        return "agent-flaw";
    }

    void propositional_agent::agnt_flaw::compute_resolvers() { }

    propositional_agent::agnt_resolver::agnt_resolver(causal_graph& g, const smt::lin& cost, agnt_flaw& f, const ratio::atom& before, const ratio::atom& after, const smt::lit& to_do) : resolver(g, cost, f), before(before), after(after), to_do(to_do) { }

    propositional_agent::agnt_resolver::~agnt_resolver() { }

    std::string propositional_agent::agnt_resolver::get_label() const {
        return "e" + std::to_string(before.state) + " <= e" + std::to_string(after.state);
    }

    bool propositional_agent::agnt_resolver::apply() {
        return g.sat.new_clause({smt::lit(chosen, false), to_do});
    }
}