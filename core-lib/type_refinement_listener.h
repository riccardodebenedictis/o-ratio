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
 * File:   type_refinement_listener.h
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 *
 * Created on April 13, 2017, 12:30 PM
 */

#ifndef TYPE_REFINEMENT_LISTENER_H
#define TYPE_REFINEMENT_LISTENER_H

#include "parser/ratioBaseListener.h"

namespace ratio {

    class solver;
    class scope;

    class type_refinement_listener : public ratioBaseListener {
    public:
        type_refinement_listener(solver& slv);
        type_refinement_listener(const type_refinement_listener& orig) = delete;
        virtual ~type_refinement_listener();

    private:
        void enterCompilation_unit(ratioParser::Compilation_unitContext* ctx) override;

        void enterEnum_declaration(ratioParser::Enum_declarationContext* ctx) override;

        void enterClass_declaration(ratioParser::Class_declarationContext* ctx) override;
        void exitClass_declaration(ratioParser::Class_declarationContext* ctx) override;

        void enterField_declaration(ratioParser::Field_declarationContext* ctx) override;

        void enterConstructor_declaration(ratioParser::Constructor_declarationContext* ctx) override;
        void exitConstructor_declaration(ratioParser::Constructor_declarationContext* ctx) override;

        void enterVoid_method_declaration(ratioParser::Void_method_declarationContext* ctx) override;
        void exitVoid_method_declaration(ratioParser::Void_method_declarationContext* ctx) override;
        void enterType_method_declaration(ratioParser::Type_method_declarationContext* ctx) override;
        void exitType_method_declaration(ratioParser::Type_method_declarationContext* ctx) override;

        void enterPredicate_declaration(ratioParser::Predicate_declarationContext* ctx) override;
        void exitPredicate_declaration(ratioParser::Predicate_declarationContext* ctx) override;

        void enterDisjunction_statement(ratioParser::Disjunction_statementContext* ctx) override;
        void exitDisjunction_statement(ratioParser::Disjunction_statementContext* ctx) override;

        void enterConjunction(ratioParser::ConjunctionContext* ctx) override;
        void exitConjunction(ratioParser::ConjunctionContext* ctx) override;

        void enterLocal_variable_statement(ratioParser::Local_variable_statementContext* ctx) override;
        void enterAssignment_statement(ratioParser::Assignment_statementContext* ctx) override;
        void enterExpression_statement(ratioParser::Expression_statementContext* ctx) override;
        void enterFormula_statement(ratioParser::Formula_statementContext* ctx) override;
        void enterReturn_statement(ratioParser::Return_statementContext* ctx) override;

        void enterQualified_id_expression(ratioParser::Qualified_id_expressionContext* ctx) override;
        void enterFunction_expression(ratioParser::Function_expressionContext* ctx) override;

    private:
        solver& _solver;
        scope* _scope;
    };
}

#endif /* TYPE_REFINEMENT_LISTENER_H */

