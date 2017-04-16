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
 * File:   enum_flaw.cpp
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 * 
 * Created on April 14, 2017, 2:28 PM
 */

#include "enum_flaw.h"
#include "causal_graph.h"

namespace cg {

    enum_flaw::enum_flaw(causal_graph& cg, ratio::enum_item& e) : flaw(cg, true), e(e) { }

    enum_flaw::~enum_flaw() { }

    bool enum_flaw::compute_resolvers(std::vector<resolver*>& rs) {
        std::unordered_set<smt::set_item*> vals = cg.set.value(e.ev);
        for (const auto& v : vals) {
            rs.push_back(new choose_value(cg, *this, *v));
        }
        return true;
    }

    enum_flaw::choose_value::choose_value(causal_graph& cg, enum_flaw& f, smt::set_item& val) : resolver(cg, smt::lin(1.0 / cg.set.value(f.e.ev).size()), f), v(f.e.ev), val(val) { }

    enum_flaw::choose_value::~choose_value() { }

    bool enum_flaw::choose_value::apply() {
        return cg.sat.new_clause({smt::lit(chosen, false), smt::lit(cg.set.allows(v, val), true)});
    }
}