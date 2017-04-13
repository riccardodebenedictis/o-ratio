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
 * File:   solver.h
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 *
 * Created on April 13, 2017, 10:54 AM
 */

#ifndef SOLVER_H
#define SOLVER_H

#include "core.h"
#include "../smt-lib/theory.h"

namespace ratio {

    class solver : public core, public smt::theory {
    public:
        solver();
        solver(const solver& orig) = delete;
        virtual ~solver();

        virtual bool new_fact(atom& a) = 0;
        virtual bool new_goal(atom& a) = 0;
        virtual void new_disjunction(env& e, disjunction& d) = 0;
        virtual bool solve() = 0;
    };
}

#endif /* SOLVER_H */

