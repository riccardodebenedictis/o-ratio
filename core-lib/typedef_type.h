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
 * File:   typedef_type.h
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 *
 * Created on April 13, 2017, 2:01 PM
 */

#ifndef TYPEDEF_TYPE_H
#define TYPEDEF_TYPE_H

#include "type.h"
#include "parser/ratioParser.h"

namespace ratio {

    class typedef_type : public type {
    public:
        typedef_type(core& c, scope& s, std::string name, type& base_type, ratioParser::ExprContext& expr_c);
        typedef_type(const typedef_type& orig) = delete;
        virtual ~typedef_type();

        expr new_instance(context& e) override;

    private:
        type& base_type;
        ratioParser::ExprContext& expr_c;
    };
}

#endif /* TYPEDEF_TYPE_H */

