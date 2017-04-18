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
 * File:   sat_value_listener.h
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 *
 * Created on April 18, 2017, 12:05 PM
 */

#ifndef SAT_VALUE_LISTENER_H
#define SAT_VALUE_LISTENER_H

#include "sat_core.h"

namespace smt {

    class sat_value_listener {
        friend class sat_core;
    public:

        sat_value_listener(sat_core& s) : sat(s) { }
        sat_value_listener(const sat_value_listener& that) = delete;

        virtual ~sat_value_listener() {
            for (const auto& v : sat_vars) {
                sat.forget(v, this);
            }
        }

    protected:

        void listen_sat(var v) {
            sat.listen(v, this);
            sat_vars.push_back(v);
        }

        virtual void sat_value_change(var v) { }

    private:
        sat_core& sat;
        std::vector<var> sat_vars;
    };
}

#endif /* SAT_VALUE_LISTENER_H */

