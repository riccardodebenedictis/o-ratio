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
 * File:   type_declaration_listener.cpp
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 * 
 * Created on April 13, 2017, 12:29 PM
 */

#include "type_declaration_listener.h"
#include "core.h"
#include "typedef_type.h"
#include "type_visitor.h"
#include "enum_type.h"

namespace ratio {

    type_declaration_listener::type_declaration_listener(core& c) : _core(c) { }

    type_declaration_listener::~type_declaration_listener() { }

    void type_declaration_listener::enterCompilation_unit(ratioParser::Compilation_unitContext* ctx) {
        _core.scopes.insert({ctx, &_core});
        _scope = &_core;
    }

    void type_declaration_listener::enterTypedef_declaration(ratioParser::Typedef_declarationContext* ctx) {
        // A new typedef type has been declared..
        typedef_type* td = new typedef_type(_core, *_scope, ctx->name->getText(), *type_visitor(_core).visit(ctx->primitive_type()).as<type*>(), *ctx->expr());
        if (core * c = dynamic_cast<core*> (_scope)) {
            c->types.insert({ctx->name->getText(), td});
        } else if (type * t = dynamic_cast<type*> (_scope)) {
            t->types.insert({ctx->name->getText(), td});
        }
    }

    void type_declaration_listener::enterEnum_declaration(ratioParser::Enum_declarationContext* ctx) { // A new enum type has been declared..
        enum_type* et = new enum_type(_core, *_scope, ctx->name->getText());
        _core.scopes.insert({ctx, et});

        // We add the enum values..
        for (const auto& cn : ctx->enum_constants()) {
            for (const auto& l : cn->StringLiteral()) {
                et->instances.push_back(_core.new_string(l->getText()));
            }
        }
        if (core * c = dynamic_cast<core*> (_scope)) {
            c->types.insert({ctx->name->getText(), et});
        } else if (type * t = dynamic_cast<type*> (_scope)) {
            t->types.insert({ctx->name->getText(), et});
        }
    }

    void type_declaration_listener::enterClass_declaration(ratioParser::Class_declarationContext* ctx) { // A new type has been declared..
        type* c_t = new type(_core, *_scope, ctx->name->getText());
        _core.scopes.insert({ctx, c_t});
        if (core * rc = dynamic_cast<core*> (_scope)) {
            rc->types.insert({ctx->name->getText(), c_t});
        } else if (type * t = dynamic_cast<type*> (_scope)) {
            t->types.insert({ctx->name->getText(), c_t});
        }

        _scope = c_t;
    }

    void type_declaration_listener::exitClass_declaration(ratioParser::Class_declarationContext* ctx) {
        _scope = &_scope->get_scope();
    }

    void type_declaration_listener::enterClass_type(ratioParser::Class_typeContext* ctx) {
        _core.scopes.insert({ctx, _scope});
    }
}