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
 * File:   field.h
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 *
 * Created on April 12, 2017, 5:33 PM
 */

#ifndef FIELD_H
#define FIELD_H

#include "env_ptr.h"
#include <string>

namespace ratio {

    class type;

    class field {
    public:
        field(const type& t, const std::string& name, bool synthetic = false);
        field(const field& orig) = delete;
        virtual ~field();

        virtual expr new_instance(env& e);

    public:
        const type& t;
        const std::string name;
        const bool synthetic;
    };
}

#endif /* FIELD_H */

