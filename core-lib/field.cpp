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
 * File:   field.cpp
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 * 
 * Created on April 12, 2017, 5:33 PM
 */

#include "field.h"
#include "type.h"
#include "item.h"
#include <assert.h>

namespace ratio {

    field::field(const type& t, const std::string& name, bool synthetic) : t(t), name(name), synthetic(synthetic) { }

    field::~field() { }

    expr field::new_instance(context& ctx) {
        assert(!synthetic);
        if (t.primitive) {
            return const_cast<type&> (t).new_instance(ctx);
        } else {
            return const_cast<type&> (t).new_existential();
        }
    }
}