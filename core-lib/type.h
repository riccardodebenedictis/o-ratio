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
 * File:   type.h
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 *
 * Created on April 12, 2017, 5:09 PM
 */

#ifndef TYPE_H
#define TYPE_H

#include "scope.h"
#include "item.h"
#include "env_ptr.h"

namespace ratio {

    class constructor;
    class atom;

    class type : public scope {
        friend class core;
        friend class type_declaration_listener;
        friend class type_refinement_listener;
    public:
        type(core& c, scope& s, const std::string& name, bool primitive = false);
        type(const type& orig) = delete;
        virtual ~type();

        std::vector<type*> get_supertypes() const noexcept;

        bool is_assignable_from(const type& t) const noexcept;

        virtual expr new_instance(context& ctx);
        virtual expr new_existential();

        std::vector<expr> get_instances() const noexcept;

        constructor & get_constructor(const std::vector<const type*>& ts) const;
        std::vector<constructor*> get_constructors() const noexcept;

        field & get_field(const std::string& name) const override;

        method & get_method(const std::string& name, const std::vector<const type*>& ts) const override;
        std::vector<method*> get_methods() const noexcept override;

        predicate & get_predicate(const std::string& name) const override;
        std::unordered_map<std::string, predicate*> get_predicates() const noexcept override;

        type & get_type(const std::string& name) const override;
        std::unordered_map<std::string, type*> get_types() const noexcept override;

    protected:
        virtual void inherit(predicate& base, predicate& derived);

        virtual void new_predicate(predicate& p) { }

    public:
        const std::string name;
        const bool primitive;

    protected:
        std::vector<type*> supertypes;
        std::vector<constructor*> constructors;
        std::unordered_map<std::string, std::vector<method*>> methods;
        std::unordered_map<std::string, type*> types;
        std::unordered_map<std::string, predicate*> predicates;
        std::vector<expr> instances;
    };

    class bool_type : public type {
    public:
        bool_type(core& c);
        bool_type(const bool_type& that) = delete;
        virtual ~bool_type();

        expr new_instance(context& ctx) override;
    };

    class int_type : public type {
    public:
        int_type(core& c);
        int_type(const int_type& that) = delete;
        virtual ~int_type();

        expr new_instance(context& ctx) override;
    };

    class real_type : public type {
    public:
        real_type(core& c);
        real_type(const real_type& that) = delete;
        virtual ~real_type();

        expr new_instance(context& ctx) override;
    };

    class string_type : public type {
    public:
        string_type(core& c);
        string_type(const string_type& that) = delete;
        virtual ~string_type();

        expr new_instance(context& ctx) override;
    };
}

#endif /* TYPE_H */

