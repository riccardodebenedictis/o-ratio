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
 * File:   defined_predicate.h
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 *
 * Created on April 13, 2017, 2:04 PM
 */

#ifndef DEFINED_PREDICATE_H
#define DEFINED_PREDICATE_H

#include "predicate.h"
#include "parser/ratioParser.h"

namespace ratio {

    class defined_predicate : public predicate {
    public:
        defined_predicate(core& c, scope& s, const std::string& name, const std::vector<field*>& args, ratioParser::BlockContext& b);
        defined_predicate(const defined_predicate& orig) = delete;
        virtual ~defined_predicate();

    private:
        ratioParser::BlockContext& block;

        bool apply_rule(atom& a) const override;
    };
}

#endif /* DEFINED_PREDICATE_H */

