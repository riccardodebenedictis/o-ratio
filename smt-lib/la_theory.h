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
 * File:   la_theory.h
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 *
 * Created on April 11, 2017, 11:14 AM
 */

#ifndef LA_THEORY_H
#define LA_THEORY_H

#include "theory.h"
#include "lin.h"
#include "interval.h"
#include <unordered_map>
#include <list>

namespace smt {

    class assertion;
    class t_row;
    class la_value_listener;

    class la_theory : public theory {
        friend class assertion;
        friend class t_row;
        friend class la_value_listener;
    public:
        la_theory(sat_core& c);
        la_theory(const la_theory& orig);
        virtual ~la_theory();

        var new_var();

        var leq(const lin& left, const lin& right);
        var geq(const lin& left, const lin& right);

        interval bounds(var v) const {
            return assigns[v];
        }

        interval bounds(const lin& l) const {
            interval b(l.known_term);
            for (const auto& term : l.vars) {
                b += bounds(term.first) * term.second;
            }
            return b;
        }

        double value(var v) const {
            return vals[v];
        }

        double value(const lin& l) const {
            double v(l.known_term);
            for (const auto& term : l.vars) {
                v += value(term.first) * term.second;
            }
            return v;
        }

    private:
        var mk_slack(const lin& l);

        constr* propagate(const lit& p) override;
        constr* check() override;
        void push() override;
        void pop() override;

        constr* assert_lower(var x_i, double val, const lit& p);
        constr* assert_upper(var x_i, double val, const lit& p);
        void update(var x_i, double v);
        void pivot_and_update(var x_i, var x_j, double v);
        void pivot(var x_i, var x_j);

        void listen(var v, la_value_listener * const l);
        void forget(var v, la_value_listener * const l);

    public:
        friend std::ostream& operator<<(std::ostream& os, const la_theory& obj);

    private:

        class layer {
        public:

            layer() { }

        public:
            // the old lower bounds (for backtracking)..
            std::unordered_map<var, double> lbs;
            // the old upper bounds (for backtracking)..
            std::unordered_map<var, double> ubs;
        };

        // the current assignments..
        std::vector<interval> assigns;
        // the current values..
        std::vector<double> vals;
        // the sparse matrix..
        std::map<var, t_row*> tableau;
        // the expressions (string to numeric variable) for which already exist slack variables..
        std::unordered_map<std::string, var> exprs;
        // the assertions (string to boolean variable) used both for reducing the number of boolean variables and for generating explanations..
        std::unordered_map<std::string, var> s_asrts;
        // the assertions (boolean variable to assertion) used for enforcing (negating) assertions..
        std::unordered_map<var, assertion*> v_asrts;
        // for each variable v, a list of assertions watching v..
        std::vector<std::vector<assertion*>> a_watches;
        // for each variable v, a list of tableau rows watching v..
        std::vector<std::set<t_row*>> t_watches;
        // we store the updated bounds..
        std::vector<layer> layers;
        std::unordered_map<var, std::list<la_value_listener*>> listening;
    };

    enum op {
        leq, geq
    };

    class assertion {
        friend class la_theory;
        friend class t_row;
    public:
        assertion(la_theory& th, op o, var b, var x, double v);
        assertion(const assertion& orig) = delete;
        virtual ~assertion();

    private:
        constr* propagate_lb(var x);
        constr* propagate_ub(var x);

    public:
        friend std::ostream& operator<<(std::ostream& os, const assertion& obj);

    private:
        la_theory& th;
        op o;
        var b;
        var x;
        double v;
    };

    class t_row {
        friend class la_theory;
    public:
        t_row(la_theory& th, var x, lin l);
        t_row(const assertion& orig) = delete;
        virtual ~t_row();

    private:
        constr* propagate_lb(var x);
        constr* propagate_ub(var x);

    public:
        friend std::ostream& operator<<(std::ostream& os, const t_row& obj);

    private:
        la_theory& th;
        var x;
        lin l;
    };
}

#endif /* LA_THEORY_H */

