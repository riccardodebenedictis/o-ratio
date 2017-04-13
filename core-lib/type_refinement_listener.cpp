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
 * File:   type_refinement_listener.cpp
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 * 
 * Created on April 13, 2017, 12:30 PM
 */

#include "type_refinement_listener.h"
#include "solver.h"
#include "enum_type.h"
#include "instantiated_field.h"
#include "default_constructor.h"
#include "defined_constructor.h"
#include "defined_method.h"
#include "defined_predicate.h"
#include "defined_conjunction.h"
#include "type_visitor.h"
#include "expression_visitor.h"

namespace ratio {

    type_refinement_listener::type_refinement_listener(solver& slv) : _solver(slv) { }

    type_refinement_listener::~type_refinement_listener() { }

    void type_refinement_listener::enterCompilation_unit(ratioParser::Compilation_unitContext* ctx) {
        _scope = _solver.scopes.at(ctx);
    }

    void type_refinement_listener::enterEnum_declaration(ratioParser::Enum_declarationContext* ctx) {
        enum_type* et = static_cast<enum_type*> (_solver.scopes.at(ctx));
        for (const auto& ec : ctx->enum_constants()) {
            if (ec->type()) {
                et->enums.push_back(static_cast<enum_type*> (type_visitor(_solver).visit(ec->type()).as<type*>()));
            }
        }
    }

    void type_refinement_listener::enterClass_declaration(ratioParser::Class_declarationContext* ctx) {
        // we set the superclasses of the type..
        _scope = _solver.scopes.at(ctx);
        if (ctx->type_list()) {
            type* t = static_cast<type*> (_scope);
            for (const auto& st : ctx->type_list()->type()) {
                t->supertypes.push_back(type_visitor(_solver).visit(st).as<type*>());
            }
        }
    }

    void type_refinement_listener::exitClass_declaration(ratioParser::Class_declarationContext* ctx) {
        // if the current type has no constructor..
        type* t = static_cast<type*> (_scope);
        if (t->constructors.empty()) {
            // .. we define a default empty constructor..
            t->constructors.push_back(new default_constructor(_solver, *_scope));
        }
        _scope = &_scope->get_scope();
    }

    void type_refinement_listener::enterField_declaration(ratioParser::Field_declarationContext* ctx) {
        // we add a field to the current scope..
        type * t = type_visitor(_solver).visit(ctx->type()).as<type*>();
        for (const auto& dec : ctx->variable_dec()) {
            if (dec->expr()) {
                instantiated_field* inst_f = new instantiated_field(*t, dec->name->getText(), *dec->expr());
                _scope->fields.insert({dec->name->getText(), inst_f});
            } else {
                field* f = new field(*t, dec->name->getText());
                _scope->fields.insert({dec->name->getText(), f});
            }
        }
    }

    void type_refinement_listener::enterConstructor_declaration(ratioParser::Constructor_declarationContext* ctx) {
        // we add a new constructor to the current type..
        // these are the parameters of the new constructor..
        std::vector<field*> args;
        if (ctx->typed_list()) {
            std::vector<ratioParser::TypeContext*> types = ctx->typed_list()->type();
            std::vector<antlr4::tree::TerminalNode*> ids = ctx->typed_list()->ID();
            for (unsigned int i = 0; i < types.size(); i++) {
                args.push_back(new field(*type_visitor(_solver).visit(types[i]).as<type*>(), ids[i]->getText()));
            }
        }

        defined_constructor* dc = new defined_constructor(_solver, *_scope, args, ctx->initializer_element(), *ctx->block());
        static_cast<type*> (_scope)->constructors.push_back(dc);
        _solver.scopes.insert({ctx, dc});
        _scope = dc;
    }

    void type_refinement_listener::exitConstructor_declaration(ratioParser::Constructor_declarationContext* ctx) {
        // we restore the scope as the enclosing scope of the current scope..
        _scope = &_scope->_scope;
    }

    void type_refinement_listener::enterVoid_method_declaration(ratioParser::Void_method_declarationContext* ctx) {
        // we add a new method without return type to the current scope..
        // these are the parameters of the new method..
        std::vector<field*> args;
        if (ctx->typed_list()) {
            std::vector<ratioParser::TypeContext*> types = ctx->typed_list()->type();
            std::vector<antlr4::tree::TerminalNode*> ids = ctx->typed_list()->ID();
            for (unsigned int i = 0; i < types.size(); i++) {
                args.push_back(new field(*type_visitor(_solver).visit(types[i]).as<type*>(), ids[i]->getText()));
            }
        }

        defined_method* m = new defined_method(_solver, *_scope, ctx->name->getText(), args, *ctx->block());
        if (core * c = dynamic_cast<core*> (_scope)) {
            if (c->methods.find(ctx->name->getText()) == c->methods.end()) {
                c->methods.insert({ctx->name->getText(), *new std::vector<method*>()});
            }
            c->methods.at(ctx->name->getText()).push_back(m);
        } else if (type * t = dynamic_cast<type*> (_scope)) {
            if (t->methods.find(ctx->name->getText()) == t->methods.end()) {
                t->methods.insert({ctx->name->getText(), *new std::vector<method*>()});
            }
            t->methods.at(ctx->name->getText()).push_back(m);
        }
        _solver.scopes.insert({ctx, m});
        _scope = m;
    }

    void type_refinement_listener::exitVoid_method_declaration(ratioParser::Void_method_declarationContext * ctx) {
        // we restore the scope as the enclosing scope of the current scope..
        _scope = &_scope->_scope;
    }

    void type_refinement_listener::enterType_method_declaration(ratioParser::Type_method_declarationContext * ctx) {
        // we add a new method with a return type to the current scope..
        // these are the parameters of the new method..
        type* return_type = type_visitor(_solver).visit(ctx->type()).as<type*>();
        std::vector<field*> args;
        if (ctx->typed_list()) {
            std::vector<ratioParser::TypeContext*> types = ctx->typed_list()->type();
            std::vector<antlr4::tree::TerminalNode*> ids = ctx->typed_list()->ID();
            for (unsigned int i = 0; i < types.size(); i++) {
                args.push_back(new field(*type_visitor(_solver).visit(types[i]).as<type*>(), ids[i]->getText()));
            }
        }

        defined_method* m = new defined_method(_solver, *_scope, ctx->name->getText(), args, *ctx->block(), return_type);
        if (core * c = dynamic_cast<core*> (_scope)) {
            if (c->methods.find(ctx->name->getText()) == c->methods.end()) {
                c->methods.insert({ctx->name->getText(), *new std::vector<method*>()});
            }
            c->methods.at(ctx->name->getText()).push_back(m);
        } else if (type * t = dynamic_cast<type*> (_scope)) {
            if (t->methods.find(ctx->name->getText()) == t->methods.end()) {
                t->methods.insert({ctx->name->getText(), *new std::vector<method*>()});
            }
            t->methods.at(ctx->name->getText()).push_back(m);
        }
        _solver.scopes.insert({ctx, m});
        _scope = m;
    }

    void type_refinement_listener::exitType_method_declaration(ratioParser::Type_method_declarationContext * ctx) {
        // we restore the scope as the enclosing scope of the current scope..
        _scope = &_scope->_scope;
    }

    void type_refinement_listener::enterPredicate_declaration(ratioParser::Predicate_declarationContext * ctx) {
        // we add a new predicate to the current scope..
        // these are the parameters of the new predicate..
        std::vector<field*> args;
        if (ctx->typed_list()) {
            std::vector<ratioParser::TypeContext*> types = ctx->typed_list()->type();
            std::vector<antlr4::tree::TerminalNode*> ids = ctx->typed_list()->ID();
            for (unsigned int i = 0; i < types.size(); i++) {
                args.push_back(new field(*type_visitor(_solver).visit(types[i]).as<type*>(), ids[i]->getText()));
            }
        }
        defined_predicate* p = new defined_predicate(_solver, *_scope, ctx->name->getText(), args, *ctx->block());

        if (ctx->type_list()) {
            for (const auto& t : ctx->type_list()->type()) {
                p->supertypes.push_back(type_visitor(_solver).visit(t).as<type*>());
            }
        }

        std::queue<type*> q;
        if (core * c = dynamic_cast<core*> (_scope)) {
            c->predicates.insert({ctx->name->getText(), p});
        } else if (type * t = dynamic_cast<type*> (_scope)) {
            t->predicates.insert({ctx->name->getText(), p});
            q.push(t);
        }
        while (!q.empty()) {
            q.front()->new_predicate(*p);
            for (const auto& st : q.front()->supertypes) {
                q.push(st);
            }
            q.pop();
        }

        _solver.scopes.insert({ctx, p});
        _scope = p;
    }

    void type_refinement_listener::exitPredicate_declaration(ratioParser::Predicate_declarationContext * ctx) {
        // we restore the scope as the enclosing scope of the current scope..
        _scope = &_scope->_scope;
    }

    void type_refinement_listener::enterDisjunction_statement(ratioParser::Disjunction_statementContext * ctx) {
        disjunction* d = new disjunction(_solver, *_scope);
        _solver.scopes.insert({ctx, d});
        _scope = d;
    }

    void type_refinement_listener::exitDisjunction_statement(ratioParser::Disjunction_statementContext * ctx) {
        // we restore the scope as the enclosing scope of the current scope..
        _scope = &_scope->_scope;
    }

    void type_refinement_listener::enterConjunction(ratioParser::ConjunctionContext * ctx) {
        defined_conjunction* dc;
        if (ctx->cost) {
            context c(&_solver);
            arith_expr cst = expression_visitor(_solver, c).visit(ctx->cost).as<expr>();
            dc = new defined_conjunction(_solver, *_scope, cst, *ctx->block());
        } else {
            arith_expr cst = _solver.new_real(1);
            dc = new defined_conjunction(_solver, *_scope, cst, *ctx->block());
        }
        static_cast<disjunction*> (_scope)->conjunctions.push_back(dc);
        _solver.scopes.insert({ctx, dc});
        _scope = dc;
    }

    void type_refinement_listener::exitConjunction(ratioParser::ConjunctionContext * ctx) {
        // we restore the scope as the enclosing scope of the current scope..
        _scope = &_scope->_scope;
    }

    void type_refinement_listener::enterLocal_variable_statement(ratioParser::Local_variable_statementContext * ctx) {
        _solver.scopes.insert({ctx, _scope});
    }

    void type_refinement_listener::enterAssignment_statement(ratioParser::Assignment_statementContext * ctx) {
        _solver.scopes.insert({ctx, _scope});
    }

    void type_refinement_listener::enterExpression_statement(ratioParser::Expression_statementContext * ctx) {
        _solver.scopes.insert({ctx, _scope});
    }

    void type_refinement_listener::enterFormula_statement(ratioParser::Formula_statementContext * ctx) {
        _solver.scopes.insert({ctx, _scope});
    }

    void type_refinement_listener::enterReturn_statement(ratioParser::Return_statementContext * ctx) {
        _solver.scopes.insert({ctx, _scope});
    }

    void type_refinement_listener::enterQualified_id_expression(ratioParser::Qualified_id_expressionContext * ctx) {
        _solver.scopes.insert({ctx, _scope});
    }

    void type_refinement_listener::enterFunction_expression(ratioParser::Function_expressionContext * ctx) {
        _solver.scopes.insert({ctx, _scope});
    }
}