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
 * File:   la_constr.h
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 *
 * Created on April 10, 2017, 5:23 PM
 */

#ifndef LA_CONSTR_H
#define LA_CONSTR_H

#include <iostream>
#include <vector>

namespace smt {

    typedef size_t var;

    class la_theory;
    class constr;

    class la_constr {
        friend class la_theory;
    public:
        la_constr(la_theory& th, std::vector<var> vars);
        la_constr(const la_constr& orig) = delete;
        virtual ~la_constr();

    private:
        virtual constr* propagate_lb(var x) = 0;
        virtual constr* propagate_ub(var x) = 0;

    protected:
        la_theory& th;
        std::vector<var> vars;
    };
}

#endif /* LA_CONSTR_H */

