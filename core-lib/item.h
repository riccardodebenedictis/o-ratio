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
 * File:   item.h
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 *
 * Created on April 12, 2017, 5:09 PM
 */

#ifndef ITEM_H
#define ITEM_H

#include "env.h"
#include "../smt-lib/sat_core.h"

namespace ratio {

    class type;

    class item : public env {
    public:
        item(core& c, env& e, const type& t);
        item(const item& orig) = delete;
        virtual ~item();

        virtual smt::var eq(item& item) = 0;
        virtual bool equates(const item& item) const = 0;

    public:
        const type& t;
    };
}

#endif /* ITEM_H */

