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
 * File:   atom_flaw.cpp
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 * 
 * Created on April 14, 2017, 2:28 PM
 */

#include "atom_flaw.h"

namespace cg {

    atom_flaw::atom_flaw(causal_graph& cg, ratio::atom& a, bool is_fact) : flaw(cg, true), a(a), is_fact(is_fact) { }

    atom_flaw::~atom_flaw() { }

    bool atom_flaw::compute_resolvers(std::vector<resolver*>& rs) {
        return true;
    }
}