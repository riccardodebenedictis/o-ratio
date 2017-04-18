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
 * File:   set_value_listener.h
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 *
 * Created on April 18, 2017, 12:11 PM
 */

#ifndef SET_VALUE_LISTENER_H
#define SET_VALUE_LISTENER_H

#include "set_theory.h"

namespace smt {

    class set_value_listener {
        friend class set_theory;
    public:

        set_value_listener(set_theory& s) : th(s) { }
        set_value_listener(const set_value_listener& that) = delete;

        virtual ~set_value_listener() {
            for (const auto& v : la_vars) {
                th.forget(v, this);
            }
        }

    protected:

        void listen_set(var v) {
            th.listen(v, this);
            la_vars.push_back(v);
        }

        virtual void set_value_change(var v) { }

    private:
        set_theory& th;
        std::vector<var> la_vars;
    };
}

#endif /* SET_VALUE_LISTENER_H */

