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

namespace ratio {

    statement_visitor::statement_visitor(core& c, context& ctx) : _core(c), ctx(ctx) { }

    statement_visitor::~statement_visitor() { }

    antlrcpp::Any statement_visitor::visitCompilation_unit(ratioParser::Compilation_unitContext* ctx) { }

    antlrcpp::Any statement_visitor::visitBlock(ratioParser::BlockContext* ctx) { }

    antlrcpp::Any statement_visitor::visitConjunction(ratioParser::ConjunctionContext* ctx) { }

    antlrcpp::Any statement_visitor::visitAssignment_statement(ratioParser::Assignment_statementContext* ctx) { }

    antlrcpp::Any statement_visitor::visitLocal_variable_statement(ratioParser::Local_variable_statementContext* ctx) { }

    antlrcpp::Any statement_visitor::visitExpression_statement(ratioParser::Expression_statementContext* ctx) { }

    antlrcpp::Any statement_visitor::visitFormula_statement(ratioParser::Formula_statementContext* ctx) { }

    antlrcpp::Any statement_visitor::visitReturn_statement(ratioParser::Return_statementContext* ctx) { }

    antlrcpp::Any statement_visitor::visitDisjunction_statement(ratioParser::Disjunction_statementContext* ctx) { }
}