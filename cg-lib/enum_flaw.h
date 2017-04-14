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
 * File:   enum_flaw.h
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 *
 * Created on April 14, 2017, 2:28 PM
 */

#ifndef ENUM_FLAW_H
#define ENUM_FLAW_H

#include "flaw.h"
#include "item.h"

namespace cg {

    class enum_flaw : public flaw {
    public:
        enum_flaw(causal_graph& cg, ratio::enum_expr& e);
        enum_flaw(const enum_flaw& orig) = delete;
        virtual ~enum_flaw();
    private:

    };
}

#endif /* ENUM_FLAW_H */

