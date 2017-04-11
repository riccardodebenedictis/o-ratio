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
 * File:   constr.h
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 *
 * Created on April 10, 2017, 11:44 AM
 */

#ifndef CONSTR_H
#define CONSTR_H

#include "lit.h"
#include <vector>

namespace smt {

    class sat_core;

    class constr {
        friend class sat_core;
    public:

        constr(sat_core& s, const std::vector<lit>& lits) : s(s), lits(lits) { }
        constr(const constr& orig) = delete;

        virtual ~constr() { }

        virtual bool propagate(const lit& p) {
            return true;
        }

        std::vector<lit> args() const {
            return lits;
        };

        virtual std::string to_string() const {
            return std::string();
        }

        friend std::ostream& operator<<(std::ostream& os, const constr& obj) {
            os << obj.to_string();
            return os;
        }

    protected:
        sat_core& s;
        std::vector<lit> lits;
    };
}

#endif /* CONSTR_H */

