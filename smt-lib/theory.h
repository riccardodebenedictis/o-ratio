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

        sat_core& get_core() const {
            return c;
        }

    protected:
        void bind(var v);
        void unbind(var v);
        void record(const std::vector<lit>& clause);

    private:
        /**
         * Asks the theory to perform propagation after the given literal has been assigned. Returns true if the propagation succeeds or false if an inconsistency is found. In case of inconsistency, the confl vector is filled with the conflicting constraint.
         * 
         * @param p the literal that has been assigned.
         * @param confl the vector of literals representing the conflicting constraint.
         * @return true if propagation succeeds or false if an inconsistency is found.
         */
        virtual bool propagate(const lit& p, std::vector<lit>& confl) = 0;
        /**
         * Checks whether the theory is consistent with the given propositional assignments. Returns true if the theory is consistent or false if an inconsistency is found. In case of inconsistency, the confl vector is filled with the conflicting constraint.
         * 
         * @return true if the theory is consistent or false if an inconsistency is found.
         */
        virtual bool check(std::vector<lit>& confl) = 0;
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

