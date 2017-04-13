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
 * File:   instantiated_field.cpp
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 * 
 * Created on April 13, 2017, 2:07 PM
 */

#include "instantiated_field.h"
#include "expression_visitor.h"
#include "item.h"

namespace ratio {

    instantiated_field::instantiated_field(const type& t, const std::string& name, ratioParser::ExprContext& expr_c) : field(t, name), expr_c(expr_c) { }

    instantiated_field::~instantiated_field() { }

    expr instantiated_field::new_instance(context& ctx) {
        return expression_visitor(ctx->get_core(), ctx).visit(&expr_c).as<expr>();
    }
}