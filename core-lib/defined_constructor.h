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
 * File:   defined_constructor.h
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 *
 * Created on April 13, 2017, 2:04 PM
 */

#ifndef DEFINED_CONSTRUCTOR_H
#define DEFINED_CONSTRUCTOR_H

namespace ratio {

    class defined_constructor {
    public:
        defined_constructor();
        defined_constructor(const defined_constructor& orig) = delete;
        virtual ~defined_constructor();
    private:

    };
}

#endif /* DEFINED_CONSTRUCTOR_H */

