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
 * File:   statement_visitor.h
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 *
 * Created on April 13, 2017, 12:31 PM
 */

#ifndef STATEMENT_VISITOR_H
#define STATEMENT_VISITOR_H

#include "parser/ratioBaseVisitor.h"
#include "env_ptr.h"

namespace ratio {

    class solver;

    class statement_visitor : public ratioBaseVisitor {
    public:
        statement_visitor(solver& s, context& ctx);
        statement_visitor(const statement_visitor& orig) = delete;
        virtual ~statement_visitor();

    private:
        antlrcpp::Any visitCompilation_unit(ratioParser::Compilation_unitContext* ctx) override;
        antlrcpp::Any visitBlock(ratioParser::BlockContext* ctx) override;
        antlrcpp::Any visitConjunction(ratioParser::ConjunctionContext* ctx) override;
        antlrcpp::Any visitAssignment_statement(ratioParser::Assignment_statementContext* ctx) override;
        antlrcpp::Any visitLocal_variable_statement(ratioParser::Local_variable_statementContext* ctx) override;
        antlrcpp::Any visitExpression_statement(ratioParser::Expression_statementContext* ctx) override;
        antlrcpp::Any visitFormula_statement(ratioParser::Formula_statementContext* ctx) override;
        antlrcpp::Any visitReturn_statement(ratioParser::Return_statementContext* ctx) override;
        antlrcpp::Any visitDisjunction_statement(ratioParser::Disjunction_statementContext* ctx) override;

    private:
        solver& _solver;
        context& ctx;
    };
}

#endif /* STATEMENT_VISITOR_H */

