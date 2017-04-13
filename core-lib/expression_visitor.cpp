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

namespace ratio {

    expression_visitor::expression_visitor(core& c, context& ctx) : _core(c), ctx(ctx) { }

    expression_visitor::~expression_visitor() { }

    antlrcpp::Any expression_visitor::visitLiteral_expression(ratioParser::Literal_expressionContext* ctx) { }

    antlrcpp::Any expression_visitor::visitParentheses_expression(ratioParser::Parentheses_expressionContext* ctx) { }

    antlrcpp::Any expression_visitor::visitMultiplication_expression(ratioParser::Multiplication_expressionContext* ctx) { }

    antlrcpp::Any expression_visitor::visitDivision_expression(ratioParser::Division_expressionContext* ctx) { }

    antlrcpp::Any expression_visitor::visitAddition_expression(ratioParser::Addition_expressionContext* ctx) { }

    antlrcpp::Any expression_visitor::visitSubtraction_expression(ratioParser::Subtraction_expressionContext* ctx) { }

    antlrcpp::Any expression_visitor::visitMinus_expression(ratioParser::Minus_expressionContext* ctx) { }

    antlrcpp::Any expression_visitor::visitNot_expression(ratioParser::Not_expressionContext* ctx) { }

    antlrcpp::Any expression_visitor::visitQualified_id(ratioParser::Qualified_idContext* ctx) { }

    antlrcpp::Any expression_visitor::visitQualified_id_expression(ratioParser::Qualified_id_expressionContext* ctx) { }

    antlrcpp::Any expression_visitor::visitFunction_expression(ratioParser::Function_expressionContext* ctx) { }

    antlrcpp::Any expression_visitor::visitRange_expression(ratioParser::Range_expressionContext* ctx) { }

    antlrcpp::Any expression_visitor::visitConstructor_expression(ratioParser::Constructor_expressionContext* ctx) { }

    antlrcpp::Any expression_visitor::visitEq_expression(ratioParser::Eq_expressionContext* ctx) { }

    antlrcpp::Any expression_visitor::visitLt_expression(ratioParser::Lt_expressionContext* ctx) { }

    antlrcpp::Any expression_visitor::visitLeq_expression(ratioParser::Leq_expressionContext* ctx) { }

    antlrcpp::Any expression_visitor::visitGeq_expression(ratioParser::Geq_expressionContext* ctx) { }

    antlrcpp::Any expression_visitor::visitGt_expression(ratioParser::Gt_expressionContext* ctx) { }

    antlrcpp::Any expression_visitor::visitNeq_expression(ratioParser::Neq_expressionContext* ctx) { }

    antlrcpp::Any expression_visitor::visitImplication_expression(ratioParser::Implication_expressionContext* ctx) { }

    antlrcpp::Any expression_visitor::visitConjunction_expression(ratioParser::Conjunction_expressionContext* ctx) { }

    antlrcpp::Any expression_visitor::visitExtc_one_expression(ratioParser::Extc_one_expressionContext* ctx) { }

    antlrcpp::Any expression_visitor::visitDisjunction_expression(ratioParser::Disjunction_expressionContext* ctx) { }
}