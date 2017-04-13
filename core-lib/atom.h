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
 * File:   atom.h
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 *
 * Created on April 12, 2017, 5:47 PM
 */

#ifndef ATOM_H
#define ATOM_H

#include "item.h"

namespace ratio {

    class predicate;
    class atom;

    class atom_state : public smt::set_item {
        friend class atom;
    private:

        atom_state() { }
        atom_state(const atom_state& that) = delete;

        virtual ~atom_state() { }
    };

    class atom : public item {
    public:
        static atom_state * const active;
        static atom_state * const inactive;
        static atom_state * const unified;
    public:
        atom(solver& slv, env& e, predicate& p);
        atom(const atom& orig);
        virtual ~atom();

    public:
        const smt::var state;
    };
}

#endif /* ATOM_H */

