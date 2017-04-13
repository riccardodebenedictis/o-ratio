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
 * File:   enum_type.h
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 *
 * Created on April 13, 2017, 2:07 PM
 */

#ifndef ENUM_TYPE_H
#define ENUM_TYPE_H

#include "type.h"

namespace ratio {

    class enum_type : public type {
        friend class type_refinement_listener;
    public:
        enum_type(solver& slv, scope& s, std::string name);
        enum_type(const enum_type& orig) = delete;
        virtual ~enum_type();

        expr new_instance(context& ctx) override;

    private:
        std::unordered_set<item*> get_all_instances() const;

    private:
        std::vector<enum_type*> enums;
    };
}

#endif /* ENUM_TYPE_H */

