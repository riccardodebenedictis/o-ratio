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
 * File:   disjunction_flaw.cpp
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 * 
 * Created on April 14, 2017, 2:28 PM
 */

#include "disjunction_flaw.h"
#include "causal_graph.h"

namespace cg {

    disjunction_flaw::disjunction_flaw(causal_graph& cg, ratio::context& e, ratio::disjunction& d) : flaw(cg, true), e(e), disj(d) { }

    disjunction_flaw::~disjunction_flaw() { }

    bool disjunction_flaw::compute_resolvers(std::vector<resolver*>& rs) {
        for (const auto& cnj : disj.get_conjunctions()) {
            ratio::context ctx(new ratio::env(cg, *e));
            rs.push_back(new choose_conjunction(cg, *this, ctx, *cnj));
        }
        return true;
    }

    disjunction_flaw::choose_conjunction::choose_conjunction(causal_graph& cg, disjunction_flaw& f, ratio::context& e, ratio::conjunction& c) : resolver(cg, c.get_cost(), f), e(e), conj(c) { }

    disjunction_flaw::choose_conjunction::~choose_conjunction() { }

    bool disjunction_flaw::choose_conjunction::apply() {
        return conj.apply(e);
    }
}