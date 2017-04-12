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
 * File:   constructor.h
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 *
 * Created on April 12, 2017, 5:47 PM
 */

#ifndef CONSTRUCTOR_H
#define CONSTRUCTOR_H

#include "scope.h"
#include "item.h"
#include "env_ptr.h"

namespace ratio {

    class constructor : public scope {
        friend class type;
    public:
        constructor(core& c, scope& s, const std::vector<field*>& args);
        constructor(const constructor& orig) = delete;
        virtual ~constructor();

        expr new_instance(env& e, const std::vector<expr>& exprs);
        virtual bool invoke(item& i, const std::vector<expr>& exprs) = 0;

    protected:
        const std::vector<field*> args;
    };
}

#endif /* CONSTRUCTOR_H */

