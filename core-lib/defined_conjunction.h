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
 * File:   defined_conjunction.h
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 *
 * Created on April 13, 2017, 2:02 PM
 */

#ifndef DEFINED_CONJUNCTION_H
#define DEFINED_CONJUNCTION_H

#include "disjunction.h"
#include "parser/ratioParser.h"

namespace ratio {

    class defined_conjunction : public conjunction {
    public:
        defined_conjunction(solver& slv, scope& s, const smt::lin& cst, ratioParser::BlockContext& b);
        defined_conjunction(const defined_conjunction& orig) = delete;
        virtual ~defined_conjunction();

    private:
        ratioParser::BlockContext& block;

        bool apply(context& ctx) const override;
    };
}

#endif /* DEFINED_CONJUNCTION_H */

