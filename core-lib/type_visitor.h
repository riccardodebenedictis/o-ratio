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
 * File:   type_visitor.h
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 *
 * Created on April 13, 2017, 2:01 PM
 */

#ifndef TYPE_VISITOR_H
#define TYPE_VISITOR_H

#include "parser/ratioBaseVisitor.h"

namespace ratio {

    class solver;

    class type_visitor : public ratioBaseVisitor {
    public:
        type_visitor(solver& slv);
        type_visitor(const type_visitor& orig) = delete;
        virtual ~type_visitor();

    private:
        antlrcpp::Any visitLiteral_expression(ratioParser::Literal_expressionContext* ctx) override;
        antlrcpp::Any visitCast_expression(ratioParser::Cast_expressionContext* ctx) override;
        antlrcpp::Any visitPrimitive_type(ratioParser::Primitive_typeContext* ctx) override;
        antlrcpp::Any visitClass_type(ratioParser::Class_typeContext* ctx) override;
        antlrcpp::Any visitQualified_id(ratioParser::Qualified_idContext* ctx) override;
        antlrcpp::Any visitQualified_id_expression(ratioParser::Qualified_id_expressionContext* ctx) override;
        antlrcpp::Any visitConstructor_expression(ratioParser::Constructor_expressionContext* ctx) override;

    private:
        solver& _solver;
    };
}

#endif /* TYPE_VISITOR_H */

