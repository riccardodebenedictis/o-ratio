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
 * File:   defined_method.cpp
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 * 
 * Created on April 13, 2017, 2:04 PM
 */

#include "defined_method.h"
#include "statement_visitor.h"

namespace ratio {

    defined_method::defined_method(core& c, scope& s, const std::string & name, const std::vector<field*>& args, ratioParser::BlockContext& b, const type * const return_type) : method(c, s, name, args, return_type), block(b) { }

    defined_method::~defined_method() { }

    bool defined_method::invoke(context& ctx, const std::vector<expr>& exprs) {
        return statement_visitor(_core, ctx).visit(&block).as<bool>();
    }
}