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
 * File:   flaw.cpp
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 * 
 * Created on April 14, 2017, 10:35 AM
 */

#include "flaw.h"
#include "sat_core.h"
#include "resolver.h"
#include "causal_graph.h"
#include <cassert>

namespace cg {

    flaw::flaw(causal_graph& g, bool exclusive) : g(g), exclusive(exclusive), supports(g.resolvers.begin(), g.resolvers.end()) {
        for (const auto& r : g.resolvers) {
            causes.push_back(r);
            r->preconditions.push_back(this);
        }
    }

    flaw::~flaw() { }

    void flaw::init() {
        assert(!initialized);
        assert(!expanded);

        // we create the in_plan variable..
        std::vector<smt::lit> cs;
        for (const auto& c : causes) {
            cs.push_back(smt::lit(c->chosen, true));
        }
        switch (cs.size()) {
            case 0:
                // the flaw is necessarily in_plan..
                in_plan = smt::TRUE;
                break;
            case 1:
                // the flaw is in_plan if its cause is in_plan..
                in_plan = cs.begin()->v;
                break;
            default:
                // the flaw is in_plan if the conjunction of its causes is in_plan..
                in_plan = g.sat.new_conj(cs);
        }
        initialized = true;
    }

    bool flaw::expand() {
        assert(initialized);
        assert(!expanded);

        // we compute the resolvers..
        compute_resolvers();
        expanded = true;

        // we add causal relations between the flaw and its resolvers (i.e., if the flaw is in_plan exactly one of its resolvers should be in plan)..
        switch (resolvers.size()) {
            case 0:
                // there is no way for solving this flaw..
                return g.sat.new_clause({smt::lit(in_plan, false)});
            case 1:
                // there is a unique way for solving this flaw: this is a trivial flaw..
                return g.sat.new_clause({smt::lit(in_plan, false), smt::lit(resolvers.front()->chosen, true)});
            default:
                // we need to take a decision for solving this flaw..
                std::vector<smt::lit> r_chs;
                for (const auto& r : resolvers) {
                    r_chs.push_back(smt::lit(r->chosen, true));
                }
                return g.sat.new_clause({smt::lit(in_plan, false), smt::lit(exclusive ? g.sat.new_exct_one(r_chs) : g.sat.new_disj(r_chs), true)});
        }
    }

    bool flaw::has_subgoals() {
        return std::any_of(resolvers.begin(), resolvers.end(), [](const resolver * r) {
            return !r->preconditions.empty();
        });
    }

    void flaw::add_resolver(resolver& r) {
        resolvers.push_back(&r);
        g.new_resolver(r);
    }

    std::string flaw::get_label() const {
        std::string lbl = "b" + std::to_string(in_plan);
        switch (g.sat.value(in_plan)) {
            case smt::True:
                lbl += "(T)";
                break;
            case smt::False:
                lbl += "(F)";
                break;
            case smt::Undefined:
                break;
            default:
                break;
        }
        lbl += " " + std::to_string(cost);
        return lbl;
    }
}