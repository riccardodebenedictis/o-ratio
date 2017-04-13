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
 * File:   typedef_type.cpp
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 * 
 * Created on April 13, 2017, 2:01 PM
 */

#include "typedef_type.h"
#include "expression_visitor.h"
#include "solver.h"

namespace ratio {

    typedef_type::typedef_type(solver& slv, scope& s, std::string name, type& base_type, ratioParser::ExprContext& expr_c) : type(slv, s, name), base_type(base_type), expr_c(expr_c) { }

    typedef_type::~typedef_type() { }

    expr typedef_type::new_instance(context& e) {
        expr i = base_type.new_instance(e);
        expr c_e = expression_visitor(_solver, e).visit(&expr_c).as<expr>();
        bool assert_facts = _solver.sat.new_clause({smt::lit(i->eq(*c_e), true)});
        assert(assert_facts && "new typedef instance creation failed..");
        return i;
    }
}