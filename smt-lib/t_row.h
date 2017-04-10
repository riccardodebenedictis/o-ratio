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
 * File:   t_row.h
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 *
 * Created on April 10, 2017, 5:25 PM
 */

#ifndef T_ROW_H
#define T_ROW_H

#include "la_constr.h"
#include "lin.h"

namespace smt {

    class t_row : public la_constr {
        friend class la_theory;
    public:
        t_row(la_theory& th, var v, lin l);
        t_row(const t_row& orig) = delete;
        virtual ~t_row();

    private:
        constr* propagate_lb(var x) override;
        constr* propagate_ub(var x) override;

    private:
        var v;
        lin l;
    };
}

#endif /* T_ROW_H */

