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
 * File:   theory.h
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 *
 * Created on April 10, 2017, 11:51 AM
 */

#ifndef THEORY_H
#define THEORY_H

#include "lit.h"
#include "constr.h"
#include <set>

namespace smt {

    class sat_core;

    class theory {
        friend class sat_core;
    public:
        theory(sat_core& c);
        theory(const theory& that) = delete;
        virtual ~theory();

    protected:
        void bind(var v);
        void unbind(var v);
        bool enqueue(const lit& p, constr * const cstr);

    private:
        /**
         * Asks the theory to perform propagation after the given literal has been assigned. Returns nullptr if propagation succedes or the conflicting constraint if an inconsistency is found.
         * 
         * @param p the literal that has been assigned.
         * @return nullptr if propagation succedes or the conflicting constraint if an inconsistency is found.
         */
        virtual constr* propagate(const lit& p) = 0;
        /**
         * Checks whether the theory is consistent with the given propositional assignments.
         * 
         * @return nullptr if the theory is consistent or the conflicting constraint if an inconsistency is found.
         */
        virtual constr* check() = 0;
        /**
         * Notifies the theory that some information for subsequent backtracking might need to be stored.
         */
        virtual void push() = 0;

        /**
         * Notifies the theory that a backtracking step is required.
         */
        virtual void pop() = 0;

    protected:
        sat_core& c;

    private:
        std::set<var> listening_on;
    };
}

#endif /* THEORY_H */

