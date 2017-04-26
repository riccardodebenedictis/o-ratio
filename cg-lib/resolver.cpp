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
 * File:   resolver.cpp
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 * 
 * Created on April 14, 2017, 10:35 AM
 */

#include "resolver.h"
#include "flaw.h"
#include "causal_graph.h"

namespace cg {

    resolver::resolver(causal_graph& g, const smt::lin& cost, flaw& e) : g(g), chosen(g.sat.new_var()), cost(cost), effect(e) {
        g.new_resolver(*this);
    }

    resolver::~resolver() { }

    double resolver::get_cost() const {
        if (g.sat.value(chosen) == smt::False) {
            // the resolver cannot be chosen..
            return std::numeric_limits<double>::infinity();
        } else {
            // the cost of the resolver is given by the cost of its most expensive precondition plus the cost of the resolver itself..
            double r_cost = preconditions.empty() ? 0.0 : -std::numeric_limits<double>::infinity();
            for (const auto& f : preconditions) {
                if (f->cost > r_cost) {
                    r_cost = f->cost;
                }
            }
            r_cost += g.la.value(cost);
            return r_cost;
        }
    }

    std::string resolver::get_label() const {
        std::string lbl = "b" + std::to_string(chosen);
        switch (g.sat.value(chosen)) {
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
        return lbl;
    }
}