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

namespace ratio {

    type_refinement_listener::type_refinement_listener(core& c) : _core(c) { }

    type_refinement_listener::~type_refinement_listener() { }

    void type_refinement_listener::enterCompilation_unit(ratioParser::Compilation_unitContext* ctx) { }

    void type_refinement_listener::enterEnum_declaration(ratioParser::Enum_declarationContext* ctx) { }

    void type_refinement_listener::enterClass_declaration(ratioParser::Class_declarationContext* ctx) { }

    void type_refinement_listener::exitClass_declaration(ratioParser::Class_declarationContext* ctx) { }

    void type_refinement_listener::enterField_declaration(ratioParser::Field_declarationContext* ctx) { }

    void type_refinement_listener::enterConstructor_declaration(ratioParser::Constructor_declarationContext* ctx) { }

    void type_refinement_listener::exitConstructor_declaration(ratioParser::Constructor_declarationContext* ctx) { }

    void type_refinement_listener::enterVoid_method_declaration(ratioParser::Void_method_declarationContext* ctx) { }

    void type_refinement_listener::exitVoid_method_declaration(ratioParser::Void_method_declarationContext* ctx) { }

    void type_refinement_listener::enterType_method_declaration(ratioParser::Type_method_declarationContext* ctx) { }

    void type_refinement_listener::exitType_method_declaration(ratioParser::Type_method_declarationContext* ctx) { }

    void type_refinement_listener::enterPredicate_declaration(ratioParser::Predicate_declarationContext* ctx) { }

    void type_refinement_listener::exitPredicate_declaration(ratioParser::Predicate_declarationContext* ctx) { }

    void type_refinement_listener::enterDisjunction_statement(ratioParser::Disjunction_statementContext* ctx) { }

    void type_refinement_listener::exitDisjunction_statement(ratioParser::Disjunction_statementContext* ctx) { }

    void type_refinement_listener::enterConjunction(ratioParser::ConjunctionContext* ctx) { }

    void type_refinement_listener::exitConjunction(ratioParser::ConjunctionContext* ctx) { }

    void type_refinement_listener::enterLocal_variable_statement(ratioParser::Local_variable_statementContext* ctx) { }

    void type_refinement_listener::enterAssignment_statement(ratioParser::Assignment_statementContext* ctx) { }

    void type_refinement_listener::enterExpression_statement(ratioParser::Expression_statementContext* ctx) { }

    void type_refinement_listener::enterFormula_statement(ratioParser::Formula_statementContext* ctx) { }

    void type_refinement_listener::enterReturn_statement(ratioParser::Return_statementContext* ctx) { }

    void type_refinement_listener::enterQualified_id_expression(ratioParser::Qualified_id_expressionContext* ctx) { }

    void type_refinement_listener::enterFunction_expression(ratioParser::Function_expressionContext* ctx) { }
}