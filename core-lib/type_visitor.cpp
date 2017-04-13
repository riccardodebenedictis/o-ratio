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
 * File:   type_visitor.cpp
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 * 
 * Created on April 13, 2017, 2:01 PM
 */

#include "type_visitor.h"

namespace ratio {

    type_visitor::type_visitor(core& c) : _core(c) { }

    type_visitor::~type_visitor() { }

    antlrcpp::Any type_visitor::visitLiteral_expression(ratioParser::Literal_expressionContext* ctx) { }

    antlrcpp::Any type_visitor::visitCast_expression(ratioParser::Cast_expressionContext* ctx) { }

    antlrcpp::Any type_visitor::visitPrimitive_type(ratioParser::Primitive_typeContext* ctx) { }

    antlrcpp::Any type_visitor::visitClass_type(ratioParser::Class_typeContext* ctx) { }

    antlrcpp::Any type_visitor::visitQualified_id(ratioParser::Qualified_idContext* ctx) { }

    antlrcpp::Any type_visitor::visitQualified_id_expression(ratioParser::Qualified_id_expressionContext* ctx) { }

    antlrcpp::Any type_visitor::visitConstructor_expression(ratioParser::Constructor_expressionContext* ctx) { }
}