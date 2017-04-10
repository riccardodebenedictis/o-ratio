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
 * File:   la_theory.cpp
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 * 
 * Created on April 10, 2017, 5:15 PM
 */

#include "la_theory.h"
#include "sat_core.h"
#include <sstream>

namespace smt {

    la_theory::la_theory(sat_core& c) : theory(c) { }

    la_theory::~la_theory() { }

    var la_theory::new_var() {
        var id = assigns.size();
        watches.push_back(std::vector<la_constr*>());
        assigns.push_back(interval());
        vals.push_back(0);
        exprs.insert({"x" + std::to_string(id), id});
        return id;
    }

    var la_theory::leq(const lin& left, const lin& right) {
        lin expr = left - right;
        std::vector<size_t> vars;
        for (const auto& term : expr.vars) {
            vars.push_back(term.first);
        }
        for (const auto& v : vars) {
            if (tableau.find(v) != tableau.end()) {
                double c = expr.vars[v];
                expr.vars.erase(v);
                expr += tableau[v]->l * c;
            }
        }

        double c_right = -expr.known_term;
        expr.known_term = 0;
        interval i = bounds(expr);
        if (i <= c_right) {
            // the constraint is already satisfied..
            return TRUE;
        } else if (i > c_right) {
            // the constraint is unsatisfable..
            return FALSE;
        } else {
            var slack = mk_slack(expr);
            std::string s_assertion = "x" + std::to_string(slack) + " <= " + std::to_string(c_right);
            if (s_asrts.find(s_assertion) != s_asrts.end()) {
                // this assertion already exists..
                return s_asrts.at(s_assertion);
            } else {
                var ctr = c.new_var();
                bind(ctr);
                s_asrts.insert({s_assertion, ctr});
                assertion* a = new assertion(*this, op::leq, ctr, slack, c_right);
                i_asrts.insert({ctr, a});
                constrs.push_back(a);
                return ctr;
            }
        }
    }

    var la_theory::geq(const lin& left, const lin& right) {
        lin expr = left - right;
        std::vector<size_t> vars;
        for (const auto& term : expr.vars) {
            vars.push_back(term.first);
        }
        for (const auto& v : vars) {
            if (tableau.find(v) != tableau.end()) {
                double c = expr.vars[v];
                expr.vars.erase(v);
                expr += tableau[v]->l * c;
            }
        }

        double c_right = -expr.known_term;
        expr.known_term = 0;
        interval i = bounds(expr);
        if (i <= c_right) {
            // the constraint is already satisfied..
            return TRUE;
        } else if (i > c_right) {
            // the constraint is unsatisfable..
            return FALSE;
        } else {
            var slack = mk_slack(expr);
            std::string s_assertion = "x" + std::to_string(slack) + " >= " + std::to_string(c_right);
            if (s_asrts.find(s_assertion) != s_asrts.end()) {
                // this assertion already exists..
                return s_asrts.at(s_assertion);
            } else {
                var ctr = c.new_var();
                bind(ctr);
                s_asrts.insert({s_assertion, ctr});
                assertion* a = new assertion(*this, op::leq, ctr, slack, c_right);
                i_asrts.insert({ctr, a});
                constrs.push_back(a);
                return ctr;
            }
        }
    }

    var la_theory::mk_slack(const lin& l) {
        std::ostringstream os;
        os << l;
        std::string s_expr = os.str();
        size_t slack;
        if (exprs.find(s_expr) != exprs.end()) {
            // the expression already exists..
            slack = exprs.at(s_expr);
        } else {
            // we need to create a new slack variable..
            slack = new_var();
            exprs.insert({s_expr, slack});
            // we set the initial bounds of the new slack variable..
            assigns[slack] = bounds(l);
            // we set the initial value of the new slack variable..
            vals[slack] = value(l);
            t_row* row = new t_row(*this, slack, l);
            // we add a new row into the tableau..
            tableau.insert({slack, row});
            // we also create a propagator to propagate bounds..
            constrs.push_back(row);
        }
        return slack;
    }

    constr* la_theory::propagate(const lit& p) { }

    constr* la_theory::check() { }

    void la_theory::push() { }

    void la_theory::pop() { }

    bool la_theory::assert_lower(var x_i, double val) { }

    bool la_theory::assert_upper(var x_i, double val) { }

    void la_theory::update(var x_i, double v) { }

    void la_theory::pivot_and_update(var x_i, var x_j, double v) { }

    void la_theory::pivot(var x_i, var x_j) { }
}