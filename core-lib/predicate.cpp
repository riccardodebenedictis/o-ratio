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
 * File:   predicate.cpp
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 * 
 * Created on April 12, 2017, 5:43 PM
 */

#include "predicate.h"
#include "field.h"
#include "atom.h"

namespace ratio {

    predicate::predicate(solver& slv, scope& s, const std::string& name, const std::vector<field*>& args) : type(slv, s, name), args(args) {
        if (type * t = dynamic_cast<type*> (&s)) {
            fields.insert({THIS_KEYWORD, new field(*t, THIS_KEYWORD, true)});
        }
        for (const auto& arg : args) {
            fields.insert({arg->name, arg});
        }
    }

    predicate::~predicate() { }

    expr predicate::new_instance(context& ctx) {
        atom * a = new atom(_solver, *ctx, *this);
        std::queue<predicate*> q;
        q.push(this);
        while (!q.empty()) {
            q.front()->instances.push_back(a);
            for (const auto& st : q.front()->supertypes) {
                q.push(static_cast<predicate*> (st));
            }
            q.pop();
        }

        return expr(a);
    }
}