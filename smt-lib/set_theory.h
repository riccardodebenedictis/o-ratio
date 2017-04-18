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
 * File:   set_theory.h
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 *
 * Created on April 12, 2017, 6:47 PM
 */

#ifndef SET_THEORY_H
#define SET_THEORY_H

#include "theory.h"
#include <unordered_set>
#include <unordered_map>
#include <list>

namespace smt {

    class set_value_listener;

    class set_item {
    public:

        set_item() { }

        virtual ~set_item() { }
    };

    class set_theory : public theory {
        friend class set_value_listener;
    public:
        set_theory(sat_core& c);
        set_theory(const set_theory& orig) = delete;
        virtual ~set_theory();

        var new_var(const std::unordered_set<set_item*>& items);

        var allows(const var& left, set_item& right) const;
        var eq(const var& left, const var& right);

        std::unordered_set<set_item*> value(var v) const;

    private:

        constr* propagate(const lit& p) override;

        constr* check() override {
            return nullptr;
        }

        void push() override { }

        void pop() override { }

        void listen(var v, set_value_listener * const l);
        void forget(var v, set_value_listener * const l);

    private:
        // the current assignments..
        std::vector<std::unordered_map<set_item*, var>> assigns;
        // the already existing expressions (string to bool variable)..
        std::unordered_map<std::string, var> exprs;
        std::unordered_map<var, var> is_contained_in;
        std::unordered_map<var, std::list<set_value_listener*>> listening;
    };
}

#endif /* SET_THEORY_H */

