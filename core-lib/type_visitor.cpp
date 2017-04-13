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
 * File:   type_visitor.cpp
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 * 
 * Created on April 13, 2017, 2:01 PM
 */

#include "type_visitor.h"
#include "solver.h"
#include "type.h"
#include "field.h"

namespace ratio {

    type_visitor::type_visitor(solver& slv) : _solver(slv) { }

    type_visitor::~type_visitor() { }

    antlrcpp::Any type_visitor::visitLiteral_expression(ratioParser::Literal_expressionContext* ctx) {
        if (ctx->literal()->numeric) {
            if (ctx->literal()->numeric->getText().find('.') != ctx->literal()->numeric->getText().npos) {
                return &_solver.get_type(REAL_KEYWORD);
            } else {
                return &_solver.get_type(INT_KEYWORD);
            }
        } else if (ctx->literal()->string) {
            return &_solver.get_type(STRING_KEYWORD);
        } else if (ctx->literal()->t) {
            return &_solver.get_type(BOOL_KEYWORD);
        } else if (ctx->literal()->f) {
            return &_solver.get_type(BOOL_KEYWORD);
        } else {
            std::unexpected();
        }
    }

    antlrcpp::Any type_visitor::visitCast_expression(ratioParser::Cast_expressionContext * ctx) {
        return visit(ctx->type()).as<type*>();
    }

    antlrcpp::Any type_visitor::visitPrimitive_type(ratioParser::Primitive_typeContext * ctx) {
        return &_solver.get_type(ctx->getText());
    }

    antlrcpp::Any type_visitor::visitClass_type(ratioParser::Class_typeContext * ctx) {
        scope * s = _solver.scopes.at(ctx);
        for (const auto& id : ctx->ID()) {
            try {
                s = &s->get_type(id->getText());
            } catch (const std::out_of_range& ex) {
                _solver.p->notifyErrorListeners(id->getSymbol(), "cannot find symbol..", nullptr);
                throw ex;
            }
        }
        return static_cast<type*> (s);
    }

    antlrcpp::Any type_visitor::visitQualified_id(ratioParser::Qualified_idContext * ctx) {
        const scope * s = _solver.scopes.at(ctx);
        if (ctx->t) {
            s = &s->get_field(THIS_KEYWORD).t;
        }
        for (const auto& id : ctx->ID()) {
            try {
                s = &s->get_field(id->getText()).t;
            } catch (const std::out_of_range& ex) {
                _solver.p->notifyErrorListeners(id->getSymbol(), "cannot find symbol..", nullptr);
                throw ex;
            }
        }
        return const_cast<type*> (static_cast<const type*> (s));
    }

    antlrcpp::Any type_visitor::visitQualified_id_expression(ratioParser::Qualified_id_expressionContext * ctx) {
        return visit(ctx->qualified_id()).as<type*>();
    }

    antlrcpp::Any type_visitor::visitConstructor_expression(ratioParser::Constructor_expressionContext * ctx) {
        return visit(ctx->type()).as<type*>();
    }
}