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
 * File:   default_constructor.h
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 *
 * Created on April 13, 2017, 2:02 PM
 */

#ifndef DEFAULT_CONSTRUCTOR_H
#define DEFAULT_CONSTRUCTOR_H

#include "constructor.h"

namespace ratio {

    class default_constructor : public constructor {
    public:
        default_constructor(solver& slv, scope& s);
        default_constructor(const default_constructor& orig) = delete;
        virtual ~default_constructor();

        bool invoke(item& i, const std::vector<expr>& exprs) override;
    };
}

#endif /* DEFAULT_CONSTRUCTOR_H */

