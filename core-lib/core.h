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
#include "../smt-lib/sat_core.h"
#include "../smt-lib/la_theory.h"
#include "../smt-lib/set_theory.h"
#include <unordered_set>

#define BOOL_KEYWORD "bool"
#define INT_KEYWORD "int"
#define REAL_KEYWORD "real"
#define STRING_KEYWORD "string"

namespace ratio {

    class atom;
    class disjunction;

    class core : public scope, public env {
    public:
        core();
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

        virtual enum_expr new_enum(const type& t, const std::unordered_set<item*>& allowed_vals);

        virtual bool new_fact(atom& a);
        virtual bool new_goal(atom& a);

        virtual void new_disjunction(env& e, disjunction& d) { }

        virtual bool solve() {
            return true;
        }

        field & get_field(const std::string& name) const override;

        method & get_method(const std::string& name, const std::vector<const type*>& ts) const override;
        std::vector<method*> get_methods() const noexcept override;

        predicate & get_predicate(const std::string& name) const override;
        std::unordered_map<std::string, predicate*> get_predicates() const noexcept override;

        type & get_type(const std::string& name) const override;
        std::unordered_map<std::string, type*> get_types() const noexcept override;

        expr get(const std::string& name) const override;

        smt::lbool bool_value(const smt::var& v) const {
            return c.value(v);
        }

        smt::var new_bool_var() {
            return c.new_var();
        }

        smt::lbool bool_value(const smt::lit& l) const {
            return c.value(l);
        }
        smt::lbool bool_value(const bool_expr& var) const noexcept;

        smt::var new_eq(const smt::lit& l, const smt::lit& r) {
            return c.new_eq(l, r);
        }

        smt::var new_conj(const std::vector<smt::lit>& ls) {
            return c.new_conj(ls);
        }

        smt::var new_disj(const std::vector<smt::lit>& ls) {
            return c.new_disj(ls);
        }

        smt::var new_exct_one(const std::vector<smt::lit>& ls) {
            return c.new_exct_one(ls);
        }

        smt::var new_arith_var() {
            return la.new_var();
        }

        smt::interval arith_bounds(smt::var v) const {
            return la.bounds(v);
        }

        smt::interval arith_bounds(const smt::lin& l) const {
            return la.bounds(l);
        }
        smt::interval arith_bounds(const arith_expr& var) const noexcept;

        double arith_value(smt::var v) const {
            return la.value(v);
        }

        double arith_value(const smt::lin& l) const {
            return la.value(l);
        }
        double arith_value(const arith_expr& var) const noexcept;

        smt::var new_leq(const smt::lin& l, const smt::lin& r) {
            return la.leq(l, r);
        }

        smt::var new_geq(const smt::lin& l, const smt::lin& r) {
            return la.geq(l, r);
        }

        smt::var new_enum_var(const std::unordered_set<smt::set_item*>& vals) {
            return set.new_var(vals);
        }

        std::unordered_set<smt::set_item*> enum_value(smt::var v) const {
            return set.value(v);
        }
        std::unordered_set<smt::set_item*> enum_value(const enum_expr& var) const noexcept;

        smt::var allows(const smt::var& l, smt::set_item& val) const {
            return set.allows(l, val);
        }

        smt::var new_eq(const smt::var& l, const smt::var& r) {
            return set.eq(l, r);
        }

    private:
        smt::sat_core c;
        smt::la_theory la;
        smt::set_theory set;

    protected:
        smt::var ctr_var = smt::TRUE;
        std::unordered_map<std::string, std::vector<method*>> methods;
        std::unordered_map<std::string, type*> types;
        std::unordered_map<std::string, predicate*> predicates;
    };
}

#endif /* CORE_H */

