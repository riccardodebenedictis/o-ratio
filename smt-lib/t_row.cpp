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
 * File:   t_row.cpp
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 * 
 * Created on April 10, 2017, 5:25 PM
 */

#include "t_row.h"
#include "utils.h"
#include "sat_core.h"

namespace smt {

    t_row::t_row(la_theory& th, var v, lin l) : la_constr(th, get_keys(l.vars)), v(v), l(l) { }

    t_row::~t_row() { }

    constr* t_row::propagate_lb(var x) { }

    constr* t_row::propagate_ub(var x) { }
}