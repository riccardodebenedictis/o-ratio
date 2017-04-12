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
 * File:   scope.cpp
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 * 
 * Created on April 12, 2017, 4:37 PM
 */

#include "scope.h"
#include "field.h"

namespace ratio {

    scope::scope(core& c, scope& s) : _core(c), _scope(s) { }

    scope::~scope() {
        for (const auto& f : fields) {
            delete f.second;
        }
    }

    field& scope::get_field(const std::string& name) const {
        if (fields.find(name) != fields.end()) {
            return *fields.at(name);
        }

        // if not here, check any enclosing scope
        return _scope.get_field(name);
    }

    std::unordered_map<std::string, field*> scope::get_fields() const noexcept {
        return fields;
    }

    method& scope::get_method(const std::string& name, const std::vector<const type*>& ts) const {
        return _scope.get_method(name, ts);
    }

    std::vector<method*> scope::get_methods() const noexcept {
        return _scope.get_methods();
    }

    type& scope::get_type(const std::string& name) const {
        return _scope.get_type(name);
    }

    std::unordered_map<std::string, type*> scope::get_types() const noexcept {
        return _scope.get_types();
    }

    predicate& scope::get_predicate(const std::string& name) const {
        return _scope.get_predicate(name);
    }

    std::unordered_map<std::string, predicate*> scope::get_predicates() const noexcept {
        return _scope.get_predicates();
    }
}