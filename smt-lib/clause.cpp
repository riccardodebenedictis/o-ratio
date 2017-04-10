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
 * File:   clause.cpp
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 * 
 * Created on April 10, 2017, 11:46 AM
 */

#include "clause.h"
#include "sat_core.h"

namespace smt {

    clause::clause(sat_core& s, const std::vector<lit>& lits) : constr(s, lits) {
        s.watches[s.index(!lits[0])].push_back(this);
        s.watches[s.index(!lits[1])].push_back(this);
    }

    clause::~clause() { }

    bool clause::propagate(const lit& p) {
        // make sure false literal is lits[1]..
        if (lits[0].v == p.v) {
            lit tmp = lits[0];
            lits[0] = lits[1];
            lits[1] = tmp;
        }

        // if 0th watch is true, the clause is already satisfied..
        if (s.value(lits[0]) == True) {
            s.watches[s.index(p)].push_back(this);
            return true;
        }

        // we look for a new literal to watch..
        for (size_t i = 1; i < lits.size(); i++) {
            if (s.value(lits[i]) != False) {
                lit tmp = lits[1];
                lits[1] = lits[i];
                lits[i] = tmp;
                s.watches[s.index(!lits[1])].push_back(this);
                return true;
            }
        }

        // clause is unit under assignment..
        s.watches[s.index(p)].push_back(this);
        return s.enqueue(lits[0], this);
    }

    std::ostream& operator<<(std::ostream& os, const clause& obj) {
        os << "(";
        for (std::vector<lit>::const_iterator it = obj.lits.begin(); it != obj.lits.end(); ++it) {
            if (it != obj.lits.begin()) {
                std::cout << " | ";
            }
            std::cout << *it;
            switch (obj.s.value(*it)) {
                case True:
                    std::cout << "(T)";
                    break;
                case False:
                    std::cout << "(F)";
                    break;
                case Undefined:
                    break;
                default:
                    break;
            }
        }
        os << ")";
        return os;
    }
}