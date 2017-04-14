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
 * File:   causal_graph.h
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 *
 * Created on April 14, 2017, 10:22 AM
 */

#ifndef CAUSAL_GRAPH_H
#define CAUSAL_GRAPH_H

#include "solver.h"
#include "type.h"
#include "atom.h"
#include "disjunction.h"

namespace cg {

    class flaw;
    class resolver;

    class causal_graph : public ratio::solver {
    public:
        causal_graph();
        causal_graph(const causal_graph& orig) = delete;
        virtual ~causal_graph();

        ratio::expr new_enum(const ratio::type& t, const std::unordered_set<ratio::item*>& allowed_vals) override;

    private:
        bool new_fact(ratio::atom& a) override;
        bool new_goal(ratio::atom& a) override;
        void new_disjunction(ratio::context& e, ratio::disjunction& d) override;

        smt::constr* propagate(const smt::lit& p) override;
        smt::constr* check() override;
        void push() override;
        void pop() override;

        bool build();
        bool add_layer();
        bool has_solution();
        bool is_deferrable(flaw& f);
        void set_cost(flaw& f, double cost);

        flaw* select_flaw();
        resolver& select_resolver(flaw& f);

    private:
        bool ok = true;
        // the reason for having introduced a flaw..
        std::unordered_map<ratio::atom*, flaw*> reason;
        // the flaw queue..
        std::queue<flaw*> flaw_q;
    };
}

#endif /* CAUSAL_GRAPH_H */

