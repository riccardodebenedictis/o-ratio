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
 * File:   type.cpp
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 * 
 * Created on April 12, 2017, 5:09 PM
 */

#include "type.h"
#include "field.h"
#include "predicate.h"
#include "method.h"
#include "constructor.h"
#include "core.h"
#include <unordered_set>
#include <cassert>
#include <algorithm>

namespace ratio {

    type::type(core& c, scope& s, const std::string& name, bool primitive) : scope(c, s), name(name), primitive(primitive) { }

    type::~type() {
        for (const auto& p : predicates) {
            delete p.second;
        }
        for (const auto& t : types) {
            delete t.second;
        }
        for (const auto& ms : methods) {
            for (const auto& m : ms.second) {
                delete m;
            }
        }
        for (const auto& c : constructors) {
            delete c;
        }
    }

    std::vector<type*> type::get_supertypes() const noexcept {
        return supertypes;
    }

    bool type::is_assignable_from(const type & t) const noexcept {
        std::queue<const type*> q;
        q.push(&t);
        while (!q.empty()) {
            if (q.front() == this) {
                return true;
            } else {
                for (const auto& st : q.front()->supertypes) {
                    q.push(st);
                }
                q.pop();
            }
        }
        return false;
    }

    expr type::new_instance(env& e) {
        expr i = new item(_core, e, *this);
        std::queue<type*> q;
        q.push(this);
        while (!q.empty()) {
            q.front()->instances.push_back(i);
            for (const auto& st : q.front()->supertypes) {
                q.push(st);
            }
            q.pop();
        }

        return i;
    }

    expr type::new_existential() {
        if (instances.size() == 1) {
            return *instances.begin();
        } else {
            std::unordered_set<item*> c_items;
            for (const auto& i : instances) {
                c_items.insert(&*i);
            }
            return _core.new_enum(*this, c_items);
        }
    }

    std::vector<expr> type::get_instances() const noexcept {
        return instances;
    }

    constructor & type::get_constructor(const std::vector<const type*>& ts) const {
        assert(std::none_of(ts.begin(), ts.end(), [](const type * t) {
            return t == nullptr; }));
        bool found = false;
        for (const auto& cnstr : constructors) {
            if (cnstr->args.size() == ts.size()) {
                found = true;
                for (unsigned int i = 0; i < ts.size(); i++) {
                    if (!cnstr->args[i]->t.is_assignable_from(*ts[i])) {
                        found = false;
                        break;
                    }
                }
                if (found) {
                    return *cnstr;
                }
            }
        }

        throw std::out_of_range(name);
    }

    std::vector<constructor*> type::get_constructors() const noexcept {
        return constructors;
    }

    field & type::get_field(const std::string & name) const {
        if (fields.find(name) != fields.end()) {
            return *fields.at(name);
        }

        // if not here, check any enclosing scope
        try {
            return _scope.get_field(name);
        } catch (const std::out_of_range& ex) {
            // if not in any enclosing scope, check any superclass
            for (const auto& st : supertypes) {
                try {
                    return st->get_field(name);
                } catch (const std::out_of_range& ex) {
                }
            }
        }

        // not found
        throw std::out_of_range(name);
    }

    method & type::get_method(const std::string & name, const std::vector<const type*>& ts) const {
        if (methods.find(name) != methods.end()) {
            bool found = false;
            for (const auto& mthd : methods.at(name)) {
                if (mthd->args.size() == ts.size()) {
                    found = true;
                    for (unsigned int i = 0; i < ts.size(); i++) {
                        if (!mthd->args[i]->t.is_assignable_from(*ts[i])) {
                            found = false;
                            break;
                        }
                    }
                    if (found) {
                        return *mthd;
                    }
                }
            }
        }

        // if not here, check any enclosing scope
        try {
            return _scope.get_method(name, ts);
        } catch (const std::out_of_range& ex) {
            // if not in any enclosing scope, check any superclass
            for (const auto& st : supertypes) {
                try {
                    return st->get_method(name, ts);
                } catch (const std::out_of_range& ex) {
                }
            }
        }

        // not found
        throw std::out_of_range(name);
    }

    std::vector<method*> type::get_methods() const noexcept {
        std::vector<method*> c_methods;
        for (const auto& ms : methods) {
            c_methods.insert(c_methods.begin(), ms.second.begin(), ms.second.end());
        }
        return c_methods;
    }

    predicate & type::get_predicate(const std::string & name) const {
        if (predicates.find(name) != predicates.end()) {
            return *predicates.at(name);
        }

        // if not here, check any enclosing scope
        try {
            return _scope.get_predicate(name);
        } catch (const std::out_of_range& ex) {
            // if not in any enclosing scope, check any superclass
            for (const auto& st : supertypes) {
                try {
                    return st->get_predicate(name);
                } catch (const std::out_of_range& ex) {
                }
            }
        }

        // not found
        throw std::out_of_range(name);
    }

    std::unordered_map<std::string, predicate*> type::get_predicates() const noexcept {
        return predicates;
    }

    type & type::get_type(const std::string & name) const {
        if (types.find(name) != types.end()) {
            return *types.at(name);
        }

        // if not here, check any enclosing scope
        try {
            return _scope.get_type(name);
        } catch (const std::out_of_range& ex) {
            // if not in any enclosing scope, check any superclass
            for (const auto& st : supertypes) {
                try {
                    return st->get_type(name);
                } catch (const std::out_of_range& ex) {
                }
            }
        }

        // not found
        throw std::out_of_range(name);
    }

    std::unordered_map<std::string, type*> type::get_types() const noexcept {
        return types;
    }

    bool_type::bool_type(core& c) : type(c, c, BOOL_KEYWORD, true) { }

    bool_type::~bool_type() { }

    expr bool_type::new_instance(env& e) {
        return _core.new_bool();
    }

    int_type::int_type(core& c) : type(c, c, INT_KEYWORD, true) { }

    int_type::~int_type() { }

    expr int_type::new_instance(env& e) {
        return _core.new_int();
    }

    real_type::real_type(core& c) : type(c, c, REAL_KEYWORD, true) { }

    real_type::~real_type() { }

    expr real_type::new_instance(env& e) {
        return _core.new_real();
    }

    string_type::string_type(core& c) : type(c, c, STRING_KEYWORD, true) { }

    string_type::~string_type() { }

    expr string_type::new_instance(env& e) {
        return _core.new_string();
    }
}