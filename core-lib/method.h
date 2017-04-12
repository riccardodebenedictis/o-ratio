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
 * File:   method.h
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 *
 * Created on April 12, 2017, 5:43 PM
 */

#ifndef METHOD_H
#define METHOD_H

#include "scope.h"
#include "item.h"
#include "env_ptr.h"

namespace ratio {

    class method : scope {
        friend class core;
        friend class type;
    public:
        method(core& c, scope& s, const std::string& name, const std::vector<field*>& args, const type * const return_type = nullptr);
        method(const method& orig) = delete;
        virtual ~method();

        const std::vector<field*> get_args() const {
            return args;
        }

        virtual bool invoke(env& e, const std::vector<expr>& exprs) = 0;

    public:
        const std::string name;

    protected:
        const std::vector<field*> args;

    public:
        const type * const return_type;
    };
}

#endif /* METHOD_H */

