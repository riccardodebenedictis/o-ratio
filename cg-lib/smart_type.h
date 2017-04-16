/*
 * Copyright (C) 2017 sydde
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
 * File:   smart_type.h
 * Author: Riccardo De Benedictis
 *
 * Created on April 16, 2017, 9.40 AM
 */

#ifndef SMART_TYPE_H
#define SMART_TYPE_H

#include "type.h"
#include "solver.h"

namespace cg {

    class flaw;

    class smart_type : public ratio::type {
    public:

        smart_type(ratio::solver& slv, scope& s, const std::string& name) : type(slv, s, name, false) { }
        smart_type(const smart_type& that) = delete;

        virtual std::vector<flaw*> get_flaws() = 0;
    };
}

#endif /* SMART_TYPE_H */

