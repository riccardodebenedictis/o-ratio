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
 * File:   disjunction.h
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 *
 * Created on April 12, 2017, 6:19 PM
 */

#ifndef DISJUNCTION_H
#define DISJUNCTION_H

#include "scope.h"
#include "env_ptr.h"
#include "item.h"
#include "la_theory.h"

namespace ratio {

    class conjunction;
    class env;

    class disjunction : public scope {
        friend class type_refinement_listener;
    public:
        disjunction(core& c, scope& s);
        disjunction(const disjunction& orig) = delete;
        virtual ~disjunction();

        std::vector<conjunction*> get_conjunctions() const;

    private:
        std::vector<conjunction*> conjunctions;
    };

    class conjunction : public scope {
    public:
        conjunction(core& c, scope& s, arith_expr& cst);
        conjunction(const conjunction& that) = delete;
        virtual ~conjunction();

        arith_expr get_cost() const {
            return cost;
        }

        virtual bool apply(context& ctx) const = 0;

    private:
        arith_expr cost;
    };
}

#endif /* DISJUNCTION_H */

