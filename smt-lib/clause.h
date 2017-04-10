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
 * File:   clause.h
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 *
 * Created on April 10, 2017, 11:46 AM
 */

#ifndef CLAUSE_H
#define CLAUSE_H

#include "constr.h"

namespace smt {

    class clause : public constr {
    public:
        clause(sat_core& s, const std::vector<lit>& lits);
        clause(const clause& orig) = delete;
        virtual ~clause();

        friend std::ostream& operator<<(std::ostream& os, const clause& obj);

    private:
        bool propagate(const lit& p) override;
    };
}

#endif /* CLAUSE_H */

