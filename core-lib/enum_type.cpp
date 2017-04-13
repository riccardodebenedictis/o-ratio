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
 * File:   enum_type.cpp
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 * 
 * Created on April 13, 2017, 2:07 PM
 */

#include "enum_type.h"
#include "core.h"

namespace ratio {

    enum_type::enum_type(core& c, scope& s, std::string name) : type(c, s, name) { }

    enum_type::~enum_type() { }

    expr enum_type::new_instance(context& ctx) {
        return _core.new_enum(*this, get_all_instances());
    }

    std::unordered_set<item*> enum_type::get_all_instances() const {
        std::unordered_set<item*> c_instances;
        for (const auto& i : instances) {
            c_instances.insert(&*i);
        }

        for (const auto& es : enums) {
            std::unordered_set<item*> es_instances = es->get_all_instances();
            c_instances.insert(es_instances.begin(), es_instances.end());
        }
        return c_instances;
    }
}