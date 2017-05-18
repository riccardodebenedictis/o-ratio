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
 * File:   statement_visitor.cpp
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 * 
 * Created on April 13, 2017, 12:31 PM
 */

#include "statement_visitor.h"
#include "solver.h"
#include "field.h"
#include "atom.h"
#include "predicate.h"
#include "disjunction.h"
#include "expression_visitor.h"
#include "type_visitor.h"

namespace ratio {

    statement_visitor::statement_visitor(solver& slv, context& cntx) : _solver(slv), cntx(cntx) { }

    statement_visitor::~statement_visitor() { }

    antlrcpp::Any statement_visitor::visitCompilation_unit(ratioParser::Compilation_unitContext* ctx) {
        for (const auto& s : ctx->statement()) {
            if (!visit(s).as<bool>()) {
                return false;
            }
        }
        return true;
    }

    antlrcpp::Any statement_visitor::visitBlock(ratioParser::BlockContext* ctx) {
        for (const auto& s : ctx->statement()) {
            if (!visit(s).as<bool>()) {
                return false;
            }
        }
        return true;
    }

    antlrcpp::Any statement_visitor::visitConjunction(ratioParser::ConjunctionContext* ctx) {
        return visit(ctx->block()).as<bool>();
    }

    antlrcpp::Any statement_visitor::visitAssignment_statement(ratioParser::Assignment_statementContext* ctx) {
        env* c_e = &*cntx;
        if (ctx->object) {
            expr ex = expression_visitor(_solver, cntx).visit(ctx->object).as<expr>();
            c_e = &*ex;
        }

        c_e->items.insert({ctx->field->getText(), expression_visitor(_solver, cntx).visit(ctx->expr()).as<expr>()});
        return true;
    }

    antlrcpp::Any statement_visitor::visitLocal_variable_statement(ratioParser::Local_variable_statementContext* ctx) {
        type * t = type_visitor(_solver).visit(ctx->type()).as<type*>();
        for (const auto& dec : ctx->variable_dec()) {
            if (dec->expr()) {
                cntx->items.insert({dec->name->getText(), expression_visitor(_solver, cntx).visit(dec->expr()).as<expr>()});
            } else if (t->primitive) {
                cntx->items.insert({dec->name->getText(), t->new_instance(cntx)});
            } else {
                cntx->items.insert({dec->name->getText(), t->new_existential()});
            }
        }
        return true;
    }

    antlrcpp::Any statement_visitor::visitExpression_statement(ratioParser::Expression_statementContext* ctx) {
        bool_expr be = expression_visitor(_solver, cntx).visit(ctx->expr()).as<expr>();
        return _solver.assert_facts({be->l});
    }

    antlrcpp::Any statement_visitor::visitFormula_statement(ratioParser::Formula_statementContext* ctx) {
        predicate * p;
        std::unordered_map<std::string, expr> assignments;
        if (ctx->object) {
            expr itm = expression_visitor(_solver, cntx).visit(ctx->object).as<expr>();
            p = &itm->t.get_predicate(ctx->predicate->getText());
            if (enum_item * ee = dynamic_cast<enum_item*> (&*itm)) {
                assignments.insert({"scope", ee});
            } else {
                assignments.insert({"scope", _solver.new_enum(itm->t, {
                        &*itm
                    })});
            }
        } else {
            p = &_solver.scopes.at(ctx)->get_scope().get_predicate(ctx->predicate->getText());
            if (&p->get_scope() != &_solver) {
                // we inherit the scope..
                assignments.insert({"scope", cntx->get("scope")});
            }
        }

        if (ctx->assignment_list()) {
            for (const auto& a : ctx->assignment_list()->assignment()) {
                assignments.insert({a->field->getText(), expression_visitor(_solver, cntx).visit(a->expr()).as<expr>()});
            }
        }

        atom * a;
        if (assignments.find("scope") == assignments.end()) {
            context c_scope = &_solver;
            a = static_cast<atom*> (&*p->new_instance(c_scope));
        } else {
            context c_scope = assignments.at("scope");
            a = static_cast<atom*> (&*p->new_instance(c_scope));
        }
        // we assign fields..
        a->items.insert(assignments.begin(), assignments.end());

        // we initialize atom's fields..
        std::queue<predicate*> q;
        q.push(p);
        while (!q.empty()) {
            for (const auto& arg : q.front()->get_args()) {
                if (a->items.find(arg->name) == a->items.end()) {
                    a->items.insert({arg->name, arg->new_instance(cntx)});
                }
            }
            for (const auto& sp : q.front()->get_supertypes()) {
                q.push(static_cast<predicate*> (sp));
            }
            q.pop();
        }

        if (ctx->fact) {
            if (!_solver.new_fact(*a)) {
                return false;
            }
        } else if (ctx->goal) {
            if (!_solver.new_goal(*a)) {
                return false;
            }
        }

        cntx->items.insert({ctx->name->getText(), expr(a)});
        return true;
    }

    antlrcpp::Any statement_visitor::visitReturn_statement(ratioParser::Return_statementContext* ctx) {
        cntx->items.insert({RETURN_KEYWORD, expression_visitor(_solver, cntx).visit(ctx->expr()).as<expr>()});
        return true;
    }

    antlrcpp::Any statement_visitor::visitDisjunction_statement(ratioParser::Disjunction_statementContext* ctx) {
        _solver.new_disjunction(cntx, *static_cast<disjunction*> (_solver.scopes.at(ctx)));
        return true;
    }
}