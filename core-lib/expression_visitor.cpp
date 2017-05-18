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
 * File:   expression_visitor.cpp
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 * 
 * Created on April 13, 2017, 2:07 PM
 */

#include "expression_visitor.h"
#include "solver.h"
#include "field.h"
#include "item.h"
#include "type.h"
#include "method.h"
#include "constructor.h"
#include "type_visitor.h"

namespace ratio {

    expression_visitor::expression_visitor(solver& slv, context& cntx) : _solver(slv), cntx(cntx) { }

    expression_visitor::~expression_visitor() { }

    antlrcpp::Any expression_visitor::visitLiteral_expression(ratioParser::Literal_expressionContext* ctx) {
        if (ctx->literal()->numeric) {
            if (ctx->literal()->numeric->getText().find('.') != ctx->literal()->numeric->getText().npos) {
                return static_cast<expr> (_solver.new_real(std::stod(ctx->literal()->numeric->getText())));
            } else {
                return static_cast<expr> (_solver.new_int(std::stol(ctx->literal()->numeric->getText())));
            }
        } else if (ctx->literal()->string) {
            std::string val = ctx->literal()->string->getText();
            val = val.substr(1, val.size() - 2);
            return static_cast<expr> (_solver.new_string(val));
        } else if (ctx->literal()->t) {
            return static_cast<expr> (_solver.new_bool(true));
        } else if (ctx->literal()->f) {
            return static_cast<expr> (_solver.new_bool(false));
        } else {
            return nullptr;
        }
    }

    antlrcpp::Any expression_visitor::visitParentheses_expression(ratioParser::Parentheses_expressionContext * ctx) {
        return visit(ctx->expr()).as<expr>();
    }

    antlrcpp::Any expression_visitor::visitMultiplication_expression(ratioParser::Multiplication_expressionContext * ctx) {
        std::vector<arith_expr> is;
        for (const auto& e : ctx->expr()) {
            is.push_back(visit(e).as<expr>());
        }
        return static_cast<expr> (_solver.mult(is));
    }

    antlrcpp::Any expression_visitor::visitDivision_expression(ratioParser::Division_expressionContext * ctx) {
        return static_cast<expr> (_solver.div(visit(ctx->expr(0)).as<expr>(), visit(ctx->expr(1)).as<expr>()));
    }

    antlrcpp::Any expression_visitor::visitAddition_expression(ratioParser::Addition_expressionContext * ctx) {
        std::vector<arith_expr> is;
        for (const auto& e : ctx->expr()) {
            is.push_back(visit(e).as<expr>());
        }
        return static_cast<expr> (_solver.add(is));
    }

    antlrcpp::Any expression_visitor::visitSubtraction_expression(ratioParser::Subtraction_expressionContext * ctx) {
        std::vector<arith_expr> is;
        for (const auto& e : ctx->expr()) {
            is.push_back(visit(e).as<expr>());
        }
        return static_cast<expr> (_solver.sub(is));
    }

    antlrcpp::Any expression_visitor::visitMinus_expression(ratioParser::Minus_expressionContext * ctx) {
        return static_cast<expr> (_solver.minus(visit(ctx->expr()).as<expr>()));
    }

    antlrcpp::Any expression_visitor::visitNot_expression(ratioParser::Not_expressionContext* ctx) {
        return static_cast<expr> (_solver.negate(visit(ctx->expr()).as<expr>()));
    }

    antlrcpp::Any expression_visitor::visitQualified_id(ratioParser::Qualified_idContext * ctx) {
        env * c_env = &*cntx;
        if (ctx->t) {
            c_env = &*c_env->get(THIS_KEYWORD);
        }
        for (const auto& id : ctx->ID()) {
            c_env = &*c_env->get(id->getText());
            if (!c_env) {
                _solver.p->notifyErrorListeners(id->getSymbol(), "cannot find symbol..", nullptr);
                return nullptr;
            }
        }
        return expr(static_cast<item*> (c_env));
    }

    antlrcpp::Any expression_visitor::visitQualified_id_expression(ratioParser::Qualified_id_expressionContext * ctx) {
        return visit(ctx->qualified_id()).as<expr>();
    }

    antlrcpp::Any expression_visitor::visitFunction_expression(ratioParser::Function_expressionContext * ctx) {
        std::vector<expr> exprs;
        std::vector<const type*> par_types;
        if (ctx->expr_list()) {
            for (const auto& ex : ctx->expr_list()->expr()) {
                expr i = expression_visitor(_solver, cntx).visit(ex).as<expr>();
                exprs.push_back(i);
                par_types.push_back(&i->t);
            }
        }

        try {
            method* m;
            if (ctx->object) {
                expr obj = visit(ctx->object).as<expr>();
                m = &obj->t.get_method(ctx->function_name->getText(), par_types);
            } else {
                m = &_solver.scopes.at(ctx)->get_method(ctx->function_name->getText(), par_types);
            }

            context c_e(new env(_solver, cntx));
            if (item * i = dynamic_cast<item*> (&*cntx->get_ctx())) {
                c_e->items.insert({THIS_KEYWORD, expr(i)});
            }
            for (unsigned int j = 0; j < m->args.size(); j++) {
                c_e->items.insert({m->args[j]->name, exprs[j]});
            }
            bool invoke = m->invoke(cntx, exprs);
            assert(invoke && "functions should not create inconsistencies..");
            return c_e->get(RETURN_KEYWORD);
        } catch (const std::out_of_range& ex) {
            _solver.p->notifyErrorListeners(ctx->function_name, "cannot find method..", nullptr);
            throw ex;
        }
    }

    antlrcpp::Any expression_visitor::visitRange_expression(ratioParser::Range_expressionContext * ctx) {
        arith_expr min = visit(ctx->min).as<expr>();
        arith_expr max = visit(ctx->max).as<expr>();
        arith_expr var = (min->t.name.compare(REAL_KEYWORD) == 0 || max->t.name.compare(REAL_KEYWORD) == 0) ? _solver.new_real() : _solver.new_int();
        bool assert_facts = _solver.assert_facts({_solver.geq(var, min)->l, _solver.leq(var, max)->l});
        assert(assert_facts && "invalid range expression..");
        return static_cast<expr> (var);
    }

    antlrcpp::Any expression_visitor::visitConstructor_expression(ratioParser::Constructor_expressionContext * ctx) {
        type * t = type_visitor(_solver).visit(ctx->type()).as<type*>();
        std::vector<expr> exprs;
        std::vector<const type*> par_types;
        if (ctx->expr_list()) {
            for (const auto& ex : ctx->expr_list()->expr()) {
                expr i = expression_visitor(_solver, cntx).visit(ex).as<expr>();
                exprs.push_back(i);
                par_types.push_back(&i->t);
            }
        }

        try {
            return t->get_constructor(par_types).new_instance(cntx, exprs);
        } catch (const std::out_of_range& ex) {
            _solver.p->notifyErrorListeners(ctx->start, "cannot find constructor..", nullptr);
            throw ex;
        }
    }

    antlrcpp::Any expression_visitor::visitEq_expression(ratioParser::Eq_expressionContext * ctx) {
        return static_cast<expr> (_solver.eq(visit(ctx->expr(0)).as<expr>(), visit(ctx->expr(1)).as<expr>()));
    }

    antlrcpp::Any expression_visitor::visitLt_expression(ratioParser::Lt_expressionContext * ctx) {
        return static_cast<expr> (_solver.lt(visit(ctx->expr(0)).as<expr>(), visit(ctx->expr(1)).as<expr>()));
    }

    antlrcpp::Any expression_visitor::visitLeq_expression(ratioParser::Leq_expressionContext * ctx) {
        return static_cast<expr> (_solver.leq(visit(ctx->expr(0)).as<expr>(), visit(ctx->expr(1)).as<expr>()));
    }

    antlrcpp::Any expression_visitor::visitGeq_expression(ratioParser::Geq_expressionContext * ctx) {
        return static_cast<expr> (_solver.geq(visit(ctx->expr(0)).as<expr>(), visit(ctx->expr(1)).as<expr>()));
    }

    antlrcpp::Any expression_visitor::visitGt_expression(ratioParser::Gt_expressionContext * ctx) {
        return static_cast<expr> (_solver.gt(visit(ctx->expr(0)).as<expr>(), visit(ctx->expr(1)).as<expr>()));
    }

    antlrcpp::Any expression_visitor::visitNeq_expression(ratioParser::Neq_expressionContext * ctx) {
        return static_cast<expr> (_solver.negate(_solver.eq(visit(ctx->expr(0)).as<expr>(), visit(ctx->expr(1)).as<expr>())));
    }

    antlrcpp::Any expression_visitor::visitImplication_expression(ratioParser::Implication_expressionContext * ctx) {
        return static_cast<expr> (_solver.disj({_solver.negate(visit(ctx->expr(0)).as<expr>()), visit(ctx->expr(1)).as<expr>()}));
    }

    antlrcpp::Any expression_visitor::visitConjunction_expression(ratioParser::Conjunction_expressionContext * ctx) {
        std::vector<bool_expr> is;
        for (const auto& e : ctx->expr()) {
            is.push_back(visit(e).as<expr>());
        }
        return static_cast<expr> (_solver.conj(is));
    }

    antlrcpp::Any expression_visitor::visitDisjunction_expression(ratioParser::Disjunction_expressionContext * ctx) {
        std::vector<bool_expr> is;
        for (const auto& e : ctx->expr()) {
            is.push_back(visit(e).as<expr>());
        }
        return static_cast<expr> (_solver.disj(is));
    }

    antlrcpp::Any expression_visitor::visitExtc_one_expression(ratioParser::Extc_one_expressionContext * ctx) {
        std::vector<bool_expr> is;
        for (const auto& e : ctx->expr()) {
            is.push_back(visit(e).as<expr>());
        }
        return static_cast<expr> (_solver.exct_one(is));
    }
}