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

namespace cg {

    causal_graph::causal_graph() { }

    causal_graph::~causal_graph() { }

    ratio::expr causal_graph::new_enum(const ratio::type& t, const std::unordered_set<ratio::item*>& allowed_vals) { }

    bool causal_graph::new_fact(ratio::atom& a) { }

    bool causal_graph::new_goal(ratio::atom& a) { }

    void causal_graph::new_disjunction(ratio::context& e, ratio::disjunction& d) { }

    smt::constr* causal_graph::propagate(const smt::lit& p) { }

    smt::constr* causal_graph::check() { }

    void causal_graph::push() { }

    void causal_graph::pop() { }

    bool causal_graph::build() { }

    bool causal_graph::add_layer() { }

    bool causal_graph::has_solution() { }

    bool causal_graph::is_deferrable(flaw& f) { }

    flaw* causal_graph::select_flaw() { }

    resolver& causal_graph::select_resolver(flaw& f) { }

    void causal_graph::set_cost(flaw& f, double cost) { }
}