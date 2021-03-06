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

    enum_flaw::enum_flaw(causal_graph& g, ratio::enum_item& e) : flaw(g, true), e(e) { }

    enum_flaw::~enum_flaw() { }

    std::string enum_flaw::get_label() const {
        return "enum";
    }

    void enum_flaw::compute_resolvers() {
        std::unordered_set<smt::set_item*> vals = g.set.value(e.ev);
        for (const auto& v : vals) {
            add_resolver(*new choose_value(g, *this, *v));
        }
    }

    enum_flaw::choose_value::choose_value(causal_graph& cg, enum_flaw& f, smt::set_item& val) : resolver(cg, smt::lin(1.0 / cg.set.value(f.e.ev).size()), f), v(f.e.ev), val(val) { }

    enum_flaw::choose_value::~choose_value() { }

    std::string enum_flaw::choose_value::get_label() const {
        return "val";
    }

    bool enum_flaw::choose_value::apply() {
        return g.sat.new_clause({smt::lit(chosen, false), smt::lit(g.set.allows(v, val), true)});
    }
}