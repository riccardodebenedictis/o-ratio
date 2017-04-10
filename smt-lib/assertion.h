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
 * File:   assertion.h
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 *
 * Created on April 10, 2017, 5:25 PM
 */

#ifndef ASSERTION_H
#define ASSERTION_H

#include "la_constr.h"

namespace smt {

    enum op {
        leq, geq
    };

    class assertion : public la_constr {
        friend class la_theory;
    public:
        assertion(la_theory& th, op o, var b, var x, double v);
        assertion(const assertion& orig) = delete;
        virtual ~assertion();

    private:
        constr* propagate_lb(var x) override;
        constr* propagate_ub(var x) override;

    private:
        op o;
        var b;
        var x;
        double v;
    };
}

#endif /* ASSERTION_H */

