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
        context itm_ctx(&i);
        std::unordered_map<std::string, field*> scope_fields = _scope.get_fields();
        for (const auto& f : scope_fields) {
            if (instantiated_field * inst_f = dynamic_cast<instantiated_field*> (f.second)) {
                set(i, f.second->name, expression_visitor(_solver, itm_ctx).visit(&inst_f->expr_c).as<expr>());
            }
        }

        context cstrctr_ctx(new env(_solver, i));
        set(*cstrctr_ctx, THIS_KEYWORD, expr(&i));
        for (unsigned int j = 0; j < args.size(); j++) {
            set(*cstrctr_ctx, args[j]->name, exprs[j]);
        }
        for (const auto& el : init_els) {
            if (scope_fields.find(el->name->getText()) != scope_fields.end()) {
                // we are assigning a value to a field..
                set(i, el->name->getText(), expression_visitor(_solver, cstrctr_ctx).visit(el->expr_list()->expr(0)).as<expr>());
            } else {
                // we are calling the constructor of a base-class..
#ifndef NDEBUG
                std::vector<type*> sts = static_cast<type&> (_scope).get_supertypes();
                assert(std::any_of(sts.begin(), sts.end(), [el](type * t) {
                    return t->name.compare(el->name->getText()) == 0;
                }));
#endif
                std::vector<expr> exprs;
                std::vector<const type*> par_types;
                if (el->expr_list()) {
                    for (const auto& ex : el->expr_list()->expr()) {
                        expr i = expression_visitor(_solver, cstrctr_ctx).visit(ex).as<expr>();
                        exprs.push_back(i);
                        par_types.push_back(&i->t);
                    }
                }
                if (!get_type(el->name->getText()).get_constructor(par_types).invoke(i, exprs)) {
                    return false;
                }
            }
        }

        // we instantiate uninstantiated fields..
        for (const auto& f : scope_fields) {
            if (!f.second->synthetic && !i.is_instantiated(f.second->name)) {
                set(i, f.second->name, f.second->new_instance(itm_ctx));
            }
        }

        return statement_visitor(_solver, cstrctr_ctx).visit(&block).as<bool>();
    }
}