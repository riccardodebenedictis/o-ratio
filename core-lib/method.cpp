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
 * File:   method.cpp
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 * 
 * Created on April 12, 2017, 5:43 PM
 */

#include "method.h"
#include "type.h"
#include "field.h"

namespace ratio {

    method::method(solver& slv, scope& s, const std::string& name, const std::vector<field*>& args, const type * const return_type) : scope(slv, s), name(name), args(args), return_type(return_type) {
        if (type * t = dynamic_cast<type*> (&s)) {
            fields.insert({THIS_KEYWORD, new field(*t, THIS_KEYWORD, true)});
        }
        if (return_type) {
            fields.insert({RETURN_KEYWORD, new field(*return_type, RETURN_KEYWORD, true)});
        }
        for (const auto& arg : args) {
            fields.insert({arg->name, arg});
        }
    }

    method::~method() { }
}