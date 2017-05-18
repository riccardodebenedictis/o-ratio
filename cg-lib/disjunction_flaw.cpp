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

    disjunction_flaw::disjunction_flaw(causal_graph& g, const ratio::context& ctx, ratio::disjunction& d) : flaw(g, true), ctx(ctx), disj(d) { }

    disjunction_flaw::~disjunction_flaw() { }

    std::string disjunction_flaw::get_label() const {
        return "disj";
    }

    void disjunction_flaw::compute_resolvers() {
        for (const auto& cnj : disj.get_conjunctions()) {
            ratio::context cnj_ctx(new ratio::env(g, ctx));
            add_resolver(*new choose_conjunction(g, *this, cnj_ctx, *cnj));
        }
    }

    disjunction_flaw::choose_conjunction::choose_conjunction(causal_graph& cg, disjunction_flaw& f, const ratio::context& ctx, ratio::conjunction& c) : resolver(cg, c.get_cost(), f), ctx(ctx), conj(c) { }

    disjunction_flaw::choose_conjunction::~choose_conjunction() { }

    std::string disjunction_flaw::choose_conjunction::get_label() const {
        return "conj";
    }

    bool disjunction_flaw::choose_conjunction::apply() {
        return conj.apply(ctx);
    }
}