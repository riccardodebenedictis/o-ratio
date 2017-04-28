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
 * File:   core.h
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 *
 * Created on April 12, 2017, 4:28 PM
 */

#ifndef CORE_H
#define CORE_H

#include "scope.h"
#include "env.h"
#include "sat_core.h"
#include "la_theory.h"
#include "set_theory.h"
#include "parser/ratioLexer.h"
#include "parser/ratioParser.h"
#include <unordered_set>

#define BOOL_KEYWORD "bool"
#define INT_KEYWORD "int"
#define REAL_KEYWORD "real"
#define STRING_KEYWORD "string"

namespace ratio {

    class solver;
    class atom;
    class disjunction;

    class core : public scope, public env {
        friend class type_declaration_listener;
        friend class type_refinement_listener;
        friend class type_visitor;
        friend class statement_visitor;
        friend class expression_visitor;
    public:
        core(solver& slv);
        core(const core& orig) = delete;
        virtual ~core();

        bool read(const std::string& script);
        bool read(const std::vector<std::string>& files);

        bool_expr new_bool();
        bool_expr new_bool(const bool& val);
        arith_expr new_int();
        arith_expr new_int(const long& val);
        arith_expr new_real();
        arith_expr new_real(const double& val);
        string_expr new_string();
        string_expr new_string(const std::string& val);
        virtual expr new_enum(const type& t, const std::unordered_set<item*>& allowed_vals);

        bool_expr negate(bool_expr var);
        bool_expr eq(bool_expr left, bool_expr right);
        bool_expr conj(const std::vector<bool_expr>& exprs);
        bool_expr disj(const std::vector<bool_expr>& exprs);
        bool_expr exct_one(const std::vector<bool_expr>& exprs);

        arith_expr add(const std::vector<arith_expr>& exprs);
        arith_expr sub(const std::vector<arith_expr>& exprs);
        arith_expr mult(const std::vector<arith_expr>& exprs);
        arith_expr div(arith_expr left, arith_expr right);
        arith_expr minus(arith_expr ex);

        bool_expr lt(arith_expr left, arith_expr right);
        bool_expr leq(arith_expr left, arith_expr right);
        bool_expr eq(arith_expr left, arith_expr right);
        bool_expr geq(arith_expr left, arith_expr right);
        bool_expr gt(arith_expr left, arith_expr right);

        bool_expr eq(expr i0, expr i1);

        bool assert_facts(const std::vector<smt::lit>& facts);

        field & get_field(const std::string& name) const override;

        method & get_method(const std::string& name, const std::vector<const type*>& ts) const override;
        std::vector<method*> get_methods() const noexcept override;

        predicate & get_predicate(const std::string& name) const override;
        std::unordered_map<std::string, predicate*> get_predicates() const noexcept override;

        type & get_type(const std::string& name) const override;
        std::unordered_map<std::string, type*> get_types() const noexcept override;

        expr get(const std::string& name) const override;

        smt::lbool bool_value(const bool_expr& var) const noexcept;
        smt::interval arith_bounds(const arith_expr& var) const noexcept;
        double arith_value(const arith_expr& var) const noexcept;
        std::unordered_set<smt::set_item*> enum_value(const enum_expr& var) const noexcept;

        friend std::ostream& operator<<(std::ostream& os, const core& obj);

    protected:
        void set_var(smt::var ctr_var);
        void restore_var();

    private:
        smt::var tmp_var;
        smt::var ctr_var = smt::TRUE;

    public:
        smt::sat_core sat;
        smt::la_theory la;
        smt::set_theory set;

    protected:
        std::unordered_map<std::string, std::vector<method*>> methods;
        std::unordered_map<std::string, type*> types;
        std::unordered_map<std::string, predicate*> predicates;

    private:
        std::vector<ratioParser*> parsers;
        std::map<antlr4::tree::ParseTree*, scope*> scopes;
        ratioParser * p;

        class snippet {
            friend class core;
        private:

            snippet(const std::string& file, ratioParser& p, ratioParser::Compilation_unitContext * const cu) : file(file), p(p), cu(cu) { }
            snippet(const snippet& that) = delete;

        private:
            const std::string file;
            ratioParser& p;
            ratioParser::Compilation_unitContext * const cu;
        };
    };
}

#endif /* CORE_H */

