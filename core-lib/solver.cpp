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
 * File:   solver.cpp
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 * 
 * Created on April 13, 2017, 10:54 AM
 */

#include "solver.h"
#include "type.h"
#include "atom.h"

namespace ratio {

    solver::solver() : core(*this), theory(sat) { }

    solver::~solver() { }

    bool solver::new_fact(atom& a) {
        if (&a.t.get_scope() == this) {
            return true;
        }
        std::queue<type*> q;
        q.push(static_cast<type*> (&a.t.get_scope()));
        while (!q.empty()) {
            if (!q.front()->new_fact(a)) {
                return false;
            }
            for (const auto& st : q.front()->get_supertypes()) {
                q.push(st);
            }
            q.pop();
        }
        return true;
    }

    bool solver::new_goal(atom& a) {
        if (&a.t.get_scope() == this) {
            return true;
        }
        std::queue<type*> q;
        q.push(static_cast<type*> (&a.t.get_scope()));
        while (!q.empty()) {
            if (!q.front()->new_goal(a)) {
                return false;
            }
            for (const auto& st : q.front()->get_supertypes()) {
                q.push(st);
            }
            q.pop();
        }
        return true;
    }
}