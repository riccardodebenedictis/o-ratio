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
 * File:   disjunction.cpp
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 * 
 * Created on April 12, 2017, 6:19 PM
 */

#include "disjunction.h"

namespace ratio {

    disjunction::disjunction(solver& slv, scope& s) : scope(slv, s) { }

    disjunction::~disjunction() {
        for (const auto& c : conjunctions) {
            delete c;
        }
    }

    conjunction::conjunction(solver& slv, scope& s, arith_expr& cst) : scope(slv, s), cost(cst) { }

    conjunction::~conjunction() { }
}