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
 * File:   scope.h
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 *
 * Created on April 12, 2017, 4:37 PM
 */

#ifndef SCOPE_H
#define SCOPE_H

#include <unordered_map>
#include <vector>

#define THIS_KEYWORD "this"
#define RETURN_KEYWORD "return"

namespace ratio {

    class solver;
    class field;
    class type;
    class method;
    class predicate;

    class scope {
        friend class type_refinement_listener;
    public:
        scope(solver& c, scope& s);
        scope(const scope& orig) = delete;
        virtual ~scope();

        solver& get_solver() const {
            return _solver;
        }

        scope& get_scope() const {
            return _scope;
        }

        virtual field& get_field(const std::string& name) const;
        std::unordered_map<std::string, field*> get_fields() const noexcept;

        virtual method& get_method(const std::string& name, const std::vector<const type*>& ts) const;
        virtual std::vector<method*> get_methods() const noexcept;

        virtual type& get_type(const std::string& name) const;
        virtual std::unordered_map<std::string, type*> get_types() const noexcept;

        virtual predicate& get_predicate(const std::string& name) const;
        virtual std::unordered_map<std::string, predicate*> get_predicates() const noexcept;

    protected:
        solver& _solver;
        scope& _scope;
        std::unordered_map<std::string, field*> fields;
    };
}

#endif /* SCOPE_H */

