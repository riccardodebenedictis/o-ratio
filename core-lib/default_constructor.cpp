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
 * File:   default_constructor.cpp
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 * 
 * Created on April 13, 2017, 2:02 PM
 */

#include "default_constructor.h"
#include "type.h"
#include "field.h"
#include <cassert>

namespace ratio {

    default_constructor::default_constructor(solver& slv, scope& s) : constructor(slv, s,{}) { }

    default_constructor::~default_constructor() { }

    bool default_constructor::invoke(item& i, const std::vector<expr>& exprs) {
        assert(exprs.empty());

        // we invoke superclasses constructors..
        for (const auto& st : static_cast<type&> (_scope).get_supertypes()) {
            st->get_constructor(std::vector<const type*>(0)).invoke(i, exprs);
        }

        // we initialize the fields..
        context ctx(&i);
        for (const auto& f : _scope.get_fields()) {
            if (!f.second->synthetic) {
                i.items.insert({f.second->name, f.second->new_instance(ctx)});
            }
        }
        return true;
    }
}