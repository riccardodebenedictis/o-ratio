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
 * File:   defined_predicate.cpp
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 * 
 * Created on April 13, 2017, 2:04 PM
 */

#include "defined_predicate.h"
#include "atom.h"
#include "statement_visitor.h"

namespace ratio {

    defined_predicate::defined_predicate(solver& slv, scope& s, const std::string & name, const std::vector<field*>& args, ratioParser::BlockContext& b) : predicate(slv, s, name, args), block(b) { }

    defined_predicate::~defined_predicate() { }

    bool defined_predicate::apply_rule(atom& a) const {
        for (const auto& sp : supertypes) {
            if (!static_cast<predicate*> (sp)->apply_rule(a)) {
                return false;
            }
        }

        context ctx(new env(_solver, a));
        ctx->items.insert({THIS_KEYWORD, &a});
        return statement_visitor(_solver, ctx).visit(&block).as<bool>();
    }
}