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
 * File:   defined_constructor.cpp
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 * 
 * Created on April 13, 2017, 2:04 PM
 */

#include "defined_constructor.h"
#include "instantiated_field.h"
#include "item.h"
#include "type.h"
#include "expression_visitor.h"
#include "statement_visitor.h"

namespace ratio {

    defined_constructor::defined_constructor(solver& slv, scope& s, const std::vector<field*>& args, std::vector<ratioParser::Initializer_elementContext*> init_els, ratioParser::BlockContext& b) : constructor(slv, s, args), init_els(init_els), block(b) { }

    defined_constructor::~defined_constructor() { }

    bool defined_constructor::invoke(item& i, const std::vector<expr>& exprs) {
        for (const auto& f : _scope.get_fields()) {
            if (instantiated_field * inst_f = dynamic_cast<instantiated_field*> (f.second)) {
                context ctx(&i);
                i.items.insert({f.second->name, expression_visitor(_solver, ctx).visit(&inst_f->expr_c).as<expr>()});
            }
        }

        context ctx(new env(_solver, i));
        ctx->items.insert({THIS_KEYWORD, expr(&i)});
        for (unsigned int j = 0; j < args.size(); j++) {
            ctx->items.insert({args[j]->name, exprs[j]});
        }
        for (const auto& el : init_els) {
            if (fields.find(el->name->getText()) != fields.end()) {
                i.items.insert({el->name->getText(), expression_visitor(_solver, ctx).visit(el->expr_list()->expr(0)).as<expr>()});
            } else {
                std::vector<expr> exprs;
                std::vector<const type*> par_types;
                if (el->expr_list()) {
                    for (const auto& ex : el->expr_list()->expr()) {
                        expr i = expression_visitor(_solver, ctx).visit(ex).as<expr>();
                        exprs.push_back(i);
                        par_types.push_back(&i->t);
                    }
                }
                if (!get_type(el->name->getText()).get_constructor(par_types).invoke(i, exprs)) {
                    return false;
                }
            }
        }

        for (const auto& f : _scope.get_fields()) {
            if (!f.second->synthetic && i.items.find(f.second->name) == i.items.end()) {
                context c(&i);
                i.items.insert({f.second->name, f.second->new_instance(c)});
            }
        }

        return statement_visitor(_solver, ctx).visit(&block).as<bool>();
    }
}