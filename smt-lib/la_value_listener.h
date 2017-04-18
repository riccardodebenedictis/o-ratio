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
 * File:   la_value_listener.h
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 *
 * Created on April 18, 2017, 12:08 PM
 */

#ifndef LA_VALUE_LISTENER_H
#define LA_VALUE_LISTENER_H

#include "la_theory.h"

namespace smt {

    class la_value_listener {
        friend class la_theory;
    public:

        la_value_listener(la_theory& s) : th(s) { }
        la_value_listener(const la_value_listener& that) = delete;

        virtual ~la_value_listener() {
            for (const auto& v : la_vars) {
                th.forget(v, this);
            }
        }

    protected:

        void listen_la(var v) {
            th.listen(v, this);
            la_vars.push_back(v);
        }

        virtual void la_value_change(var v) { }

    private:
        la_theory& th;
        std::vector<var> la_vars;
    };
}

#endif /* LA_VALUE_LISTENER_H */

