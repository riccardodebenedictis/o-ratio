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
 * File:   env.cpp
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 * 
 * Created on April 12, 2017, 4:38 PM
 */

#include "env.h"
#include "solver.h"
#include "item.h"
#include <cassert>

namespace ratio {

    env::env(solver& slv, env& e) : ref_count(this == &slv), _solver(slv), _env(e) { }

    env::~env() {
        assert(!ref_count || (this == &_env && ref_count));
    }

    expr env::get(const std::string& name) const {
        if (items.find(name) != items.end()) {
            return items.at(name);
        }

        // if not here, check any enclosing environment
        return _env.get(name);
    }

    std::unordered_map<std::string, expr> env::get_items() const noexcept {
        return items;
    }

    bool env::is_instantiated(const std::string& name) const {
        return items.find(name) != items.end();
    }
}