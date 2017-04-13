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
 * File:   instantiated_field.h
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 *
 * Created on April 13, 2017, 2:07 PM
 */

#ifndef INSTANTIATED_FIELD_H
#define INSTANTIATED_FIELD_H

#include "field.h"
#include "parser/ratioParser.h"

namespace ratio {

    class instantiated_field : public field {
        friend class defined_constructor;
    public:
        instantiated_field(const type& t, const std::string& name, ratioParser::ExprContext& expr_c);
        instantiated_field(const instantiated_field& orig) = delete;
        virtual ~instantiated_field();

        expr new_instance(context& ctx) override;

    private:
        ratioParser::ExprContext& expr_c;
    };
}

#endif /* INSTANTIATED_FIELD_H */

