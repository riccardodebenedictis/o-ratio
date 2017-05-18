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
 * File:   atom.cpp
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 * 
 * Created on April 12, 2017, 5:47 PM
 */

#include "atom.h"
#include "predicate.h"
#include "solver.h"

namespace ratio {

    atom_state * const atom::active = new atom_state();
    atom_state * const atom::inactive = new atom_state();
    atom_state * const atom::unified = new atom_state();

    atom::atom(solver& slv, const context& ctx, predicate& p) : item(slv, ctx, p), state(slv.set.new_var({atom::active, atom::inactive, atom::unified})) { }

    atom::~atom() { }
}