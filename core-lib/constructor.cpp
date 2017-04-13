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
 * File:   constructor.cpp
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 * 
 * Created on April 12, 2017, 5:47 PM
 */

#include "constructor.h"
#include "field.h"
#include "type.h"
#include <cassert>

namespace ratio {

    constructor::constructor(core& c, scope& s, const std::vector<field*>& args) : scope(c, s), args(args) {
        fields.insert({THIS_KEYWORD, new field(static_cast<type&> (s), THIS_KEYWORD, true)});
        for (const auto& arg : args) {
            fields.insert({arg->name, new field(arg->t, arg->name)});
        }
    }

    constructor::~constructor() { }

    expr constructor::new_instance(context& ctx, const std::vector<expr>& exprs) {
        assert(args.size() == exprs.size());

        type& t = static_cast<type&> (_scope);
        expr i = t.new_instance(ctx);

        invoke(*i, exprs);

        return i;
    }
}