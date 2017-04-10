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
 * Created on April 10, 2017, 5:15 PM
 */

#ifndef LA_THEORY_H
#define LA_THEORY_H

#include "theory.h"
#include "lin.h"
#include "interval.h"
#include "t_row.h"
#include "assertion.h"
#include <unordered_map>

namespace smt {

    class la_theory : public theory {
        friend class la_constr;
    public:
        la_theory(sat_core& c);
        la_theory(const la_theory& orig) = delete;
        virtual ~la_theory();

        /**
         * Creates a new arithmetic variable.
         * 
         * @return an unsigned int representing the new arithmetic variable.
         */
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

    private:
        // collection of problem constraints..
        std::vector<la_constr*> constrs;
        // for each variable v, a list of constraints watching v..
        std::vector<std::set<la_constr*>> watches;
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
        std::unordered_map<var, assertion*> i_asrts;
    };
}

#endif /* LA_THEORY_H */

