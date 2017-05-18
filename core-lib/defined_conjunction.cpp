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
 * File:   defined_conjunction.cpp
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 * 
 * Created on April 13, 2017, 2:02 PM
 */

#include "defined_conjunction.h"
#include "statement_visitor.h"
#include "env.h"

namespace ratio {

    defined_conjunction::defined_conjunction(solver& slv, scope& s, const smt::lin& cst, ratioParser::BlockContext& b) : conjunction(slv, s, cst), block(b) { }

    defined_conjunction::~defined_conjunction() { }

    bool defined_conjunction::apply(context& ctx) const {
        context c(new env(_solver, ctx));
        return statement_visitor(_solver, c).visit(&block).as<bool>();
    }
}