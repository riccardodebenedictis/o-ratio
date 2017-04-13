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
 * File:   core.cpp
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 * 
 * Created on April 12, 2017, 4:28 PM
 */

#include "core.h"
#include "type.h"
#include "type_declaration_listener.h"
#include "type_refinement_listener.h"
#include "statement_visitor.h"

namespace ratio {

    core::core() : scope(*this, *this), env(*this, *this), sat(), la(sat), set(sat) {
        types.insert({BOOL_KEYWORD, new bool_type(*this)});
        types.insert({INT_KEYWORD, new int_type(*this)});
        types.insert({REAL_KEYWORD, new real_type(*this)});
        types.insert({STRING_KEYWORD, new string_type(*this)});
    }

    core::~core() {
        for (const auto& p : parsers) {
            delete p;
        }
        for (const auto& p : predicates) {
            delete p.second;
        }
        for (const auto& t : types) {
            delete t.second;
        }
        for (const auto& ms : methods) {
            for (const auto& m : ms.second) {
                delete m;
            }
        }
    }

    bool core::read(const std::string& script) {
        p = new ratioParser(new antlr4::CommonTokenStream(new ratioLexer(new antlr4::ANTLRInputStream(script))));
        parsers.push_back(p);
        ratioParser::Compilation_unitContext* cu = p->compilation_unit();
        type_declaration_listener td(*this);
        type_refinement_listener tr(*this);
        antlr4::tree::ParseTreeWalker::DEFAULT.walk(&td, cu);
        antlr4::tree::ParseTreeWalker::DEFAULT.walk(&tr, cu);
        context ctx(this);
        if (!statement_visitor(*this, ctx).visit(cu).as<bool>()) {
            return false;
        }
        p = nullptr;
        return sat.check();
    }

    bool core::read(const std::vector<std::string>& files) {
        std::vector<snippet*> snippets;
        for (const auto& f : files) {
            p = new ratioParser(new antlr4::CommonTokenStream(new ratioLexer(new antlr4::ANTLRFileStream(f))));
            parsers.push_back(p);
            snippet* s = new snippet(f, *p, p->compilation_unit());
            snippets.push_back(s);
        }
        type_declaration_listener td(*this);
        for (const auto& s : snippets) {
            antlr4::tree::ParseTreeWalker::DEFAULT.walk(&td, s->cu);
        }
        type_refinement_listener tr(*this);
        for (const auto& s : snippets) {
            antlr4::tree::ParseTreeWalker::DEFAULT.walk(&tr, s->cu);
        }
        context ctx(this);
        statement_visitor sv(*this, ctx);
        for (const auto& s : snippets) {
            p = &s->p;
            if (!sv.visit(s->cu).as<bool>()) {
                return false;
            }
        }
        p = nullptr;
        return sat.check();
    }

    bool_expr core::new_bool() { }

    bool_expr core::new_bool(const bool& val) { }

    arith_expr core::new_int() { }

    arith_expr core::new_int(const long& val) { }

    arith_expr core::new_real() { }

    arith_expr core::new_real(const double& val) { }

    string_expr core::new_string() { }

    string_expr core::new_string(const std::string& val) { }

    enum_expr core::new_enum(const type& t, const std::unordered_set<item*>& allowed_vals) { }

    bool_expr core::negate(bool_expr var) { }

    bool_expr core::eq(bool_expr left, bool_expr right) { }

    bool_expr core::conj(const std::vector<bool_expr>& exprs) { }

    bool_expr core::disj(const std::vector<bool_expr>& exprs) { }

    bool_expr core::exct_one(const std::vector<bool_expr>& exprs) { }

    arith_expr core::add(const std::vector<arith_expr>& exprs) { }

    arith_expr core::sub(const std::vector<arith_expr>& exprs) { }

    arith_expr core::mult(const std::vector<arith_expr>& exprs) { }

    arith_expr core::div(arith_expr left, arith_expr right) { }

    arith_expr core::minus(arith_expr ex) { }

    bool_expr core::lt(arith_expr left, arith_expr right) { }

    bool_expr core::leq(arith_expr left, arith_expr right) { }

    bool_expr core::eq(arith_expr left, arith_expr right) { }

    bool_expr core::geq(arith_expr left, arith_expr right) { }

    bool_expr core::gt(arith_expr left, arith_expr right) { }

    bool_expr core::eq(expr left, expr right) { }

    bool core::assert_facts(const std::vector<smt::lit>& facts) { }

    field& core::get_field(const std::string& name) const { }

    method& core::get_method(const std::string& name, const std::vector<const type*>& ts) const { }

    std::vector<method*> core::get_methods() const noexcept { }

    predicate& core::get_predicate(const std::string& name) const { }

    std::unordered_map<std::string, predicate*> core::get_predicates() const noexcept { }

    type& core::get_type(const std::string& name) const { }

    std::unordered_map<std::string, type*> core::get_types() const noexcept { }

    expr core::get(const std::string& name) const { }

    smt::lbool core::bool_value(const bool_expr& var) const noexcept { }

    smt::interval core::arith_bounds(const arith_expr& var) const noexcept { }

    double core::arith_value(const arith_expr& var) const noexcept { }

    std::unordered_set<smt::set_item*> core::enum_value(const enum_expr& var) const noexcept { }
}