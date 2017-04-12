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
 * File:   sat_core.h
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 *
 * Created on April 10, 2017, 11:43 AM
 */

#ifndef SAT_CORE_H
#define SAT_CORE_H

#include "lit.h"
#include "constr.h"
#include <vector>
#include <queue>
#include <list>
#include <unordered_map>

namespace smt {

    static const var FALSE = 0;
    static const var TRUE = 1;

    class theory;

    enum lbool {
        True, False, Undefined
    };

    class sat_core {
        friend class clause;
        friend class theory;
    public:
        sat_core();
        sat_core(const sat_core& orig) = delete;
        virtual ~sat_core();
        var new_var();

        bool eq(const lit& left, const lit& right) {
            return new_clause({!left, right}) && new_clause({left, !right});
        }

        bool new_clause(const std::vector<lit>& lits);
        bool exct_one(const std::vector<lit>& lits);

        bool assume(const lit& p);

        lbool value(var x) const {
            return assigns[x];
        }

        lbool value(const lit& p) const {
            switch (value(p.v)) {
                case True:
                    return p.sign ? True : False;
                case False:
                    return p.sign ? False : True;
                case Undefined:
                    return Undefined;
                default:
                    throw std::logic_error("invalid value..");
            }
        }

        void pop();

        bool root_level() {
            return trail_lim.empty();
        }

        bool check();

    private:
        constr* propagate();
        void analyze(const constr& confl, std::vector<lit>& out_learnt, size_t& out_btlevel);
        void record(const std::vector<lit>& lits);

        bool enqueue(const lit& p, constr * const c = nullptr);
        void pop_one();

        size_t index(const lit& p) const {
            return p.sign ? p.v << 1 : (p.v << 1) ^ 1;
        }

    private:
        void add_theory(theory& th);
        void remove_theory(theory& th);

        void bind(var var, theory& th);
        void unbind(var var, theory& th);

    public:
        friend std::ostream& operator<<(std::ostream& os, const sat_core& obj);

    private:
        // collection of problem constraints..
        std::vector<constr*> constrs;
        // for each variable v, a list of constraints watching v..
        std::vector<std::vector<constr*>> watches;
        // propagation queue..
        std::queue<lit> prop_q;
        // the current assignments..
        std::vector<lbool> assigns;
        // the list of assignment in chronological order..
        std::vector<lit> trail;
        // separator literals for different decision levels in 'trail'..
        std::vector<lit> trail_lim;
        // for each variable, the constraint that implied its value..
        std::vector<constr*> reason;
        // for each variable, the decision level it was assigned..
        std::vector<size_t> level;

        std::vector<theory*> theories;
        std::unordered_map<var, std::list<theory*>> bounds;
    };
}

#endif /* SAT_CORE_H */

