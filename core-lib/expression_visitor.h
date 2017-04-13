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
 * File:   expression_visitor.h
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 *
 * Created on April 13, 2017, 2:07 PM
 */

#ifndef EXPRESSION_VISITOR_H
#define EXPRESSION_VISITOR_H

#include "parser/ratioBaseVisitor.h"
#include "env_ptr.h"

namespace ratio {

    class solver;

    class expression_visitor : public ratioBaseVisitor {
    public:
        expression_visitor(solver& slv, context& cntx);
        expression_visitor(const expression_visitor& orig) = delete;
        virtual ~expression_visitor();

    private:
        antlrcpp::Any visitLiteral_expression(ratioParser::Literal_expressionContext* ctx) override;
        antlrcpp::Any visitParentheses_expression(ratioParser::Parentheses_expressionContext* ctx) override;
        antlrcpp::Any visitMultiplication_expression(ratioParser::Multiplication_expressionContext* ctx) override;
        antlrcpp::Any visitDivision_expression(ratioParser::Division_expressionContext* ctx) override;
        antlrcpp::Any visitAddition_expression(ratioParser::Addition_expressionContext* ctx) override;
        antlrcpp::Any visitSubtraction_expression(ratioParser::Subtraction_expressionContext* ctx) override;
        antlrcpp::Any visitMinus_expression(ratioParser::Minus_expressionContext* ctx) override;
        antlrcpp::Any visitNot_expression(ratioParser::Not_expressionContext* ctx) override;
        antlrcpp::Any visitQualified_id(ratioParser::Qualified_idContext *ctx) override;
        antlrcpp::Any visitQualified_id_expression(ratioParser::Qualified_id_expressionContext* ctx) override;
        antlrcpp::Any visitFunction_expression(ratioParser::Function_expressionContext* ctx) override;
        antlrcpp::Any visitRange_expression(ratioParser::Range_expressionContext* ctx) override;
        antlrcpp::Any visitConstructor_expression(ratioParser::Constructor_expressionContext* ctx) override;
        antlrcpp::Any visitEq_expression(ratioParser::Eq_expressionContext* ctx) override;
        antlrcpp::Any visitLt_expression(ratioParser::Lt_expressionContext* ctx) override;
        antlrcpp::Any visitLeq_expression(ratioParser::Leq_expressionContext* ctx) override;
        antlrcpp::Any visitGeq_expression(ratioParser::Geq_expressionContext* ctx) override;
        antlrcpp::Any visitGt_expression(ratioParser::Gt_expressionContext* ctx) override;
        antlrcpp::Any visitNeq_expression(ratioParser::Neq_expressionContext* ctx) override;
        antlrcpp::Any visitImplication_expression(ratioParser::Implication_expressionContext* ctx) override;
        antlrcpp::Any visitConjunction_expression(ratioParser::Conjunction_expressionContext* ctx) override;
        antlrcpp::Any visitDisjunction_expression(ratioParser::Disjunction_expressionContext* ctx) override;
        antlrcpp::Any visitExtc_one_expression(ratioParser::Extc_one_expressionContext* ctx) override;

    private:
        solver& _solver;
        context& cntx;
    };
}

#endif /* EXPRESSION_VISITOR_H */

