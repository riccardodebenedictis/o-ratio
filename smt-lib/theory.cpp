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
 * File:   theory.cpp
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 * 
 * Created on April 10, 2017, 11:51 AM
 */

#include "theory.h"
#include "sat_core.h"
#include <cassert>

namespace smt {

    theory::theory(sat_core& c) : c(c) {
        c.add_theory(*this);
    }

    theory::~theory() {
        for (const auto& lo : listening_on) {
            c.unbind(lo, *this);
        }
        listening_on.clear();
        c.remove_theory(*this);
    }

    void theory::bind(size_t var) {
        if (listening_on.find(var) == listening_on.end()) {
            listening_on.insert(var);
            c.bind(var, *this);
        }
    }

    void theory::unbind(size_t var) {
        assert(listening_on.find(var) != listening_on.end());
        listening_on.erase(var);
        c.unbind(var, *this);
    }

    bool theory::enqueue(const lit& p, constr * const cstr) {
        return c.enqueue(p, cstr);
    }
}