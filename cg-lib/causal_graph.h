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
#ifndef N_CAUSAL_GRAPH_LISTENERS
    class causal_graph_listener;
#endif

    class causal_graph : public ratio::solver {
        friend class flaw;
        friend class atom_flaw;
#ifndef N_CAUSAL_GRAPH_LISTENERS
        friend class causal_graph_listener;
#endif
    public:
        causal_graph();
        causal_graph(const causal_graph& orig) = delete;
        virtual ~causal_graph();

        ratio::expr new_enum(const ratio::type& t, const std::unordered_set<ratio::item*>& allowed_vals) override;

        bool solve() override;

    private:
        bool new_fact(ratio::atom& a) override;
        bool new_goal(ratio::atom& a) override;
        void new_disjunction(ratio::context& e, ratio::disjunction& d) override;

        void new_flaw(flaw& f);
        void new_causal_link(flaw& f, resolver& r);

        smt::constr* propagate(const smt::lit& p) override;
        smt::constr* check() override;
        void push() override;
        void pop() override;

        bool build();
        bool add_layer();
        bool has_solution();
        bool is_deferrable(flaw& f);
        void set_cost(flaw& f, double cost);
        bool has_inconsistencies();

        flaw* select_flaw();
        resolver& select_resolver(flaw& f);

    private:

        struct layer {

            layer(resolver* r) : r(r) { }

            resolver* r;
            // the estimated flaw costs..
            std::unordered_map<flaw*, double> old_costs;
            // the new flaws..
            std::unordered_set<flaw*> new_flaws;
            // the solved flaws..
            std::unordered_set<flaw*> solved_flaws;
        };

        bool ok = true;
        // the reason for having introduced a flaw..
        std::unordered_map<ratio::atom*, flaw*> reason;
        // the flaw queue..
        std::queue<flaw*> flaw_q;
        // the current assumed resolvers..
        std::list<resolver*> resolvers;
        // the current flaws..
        std::unordered_set<flaw*> flaws;
        // the in_plan variables (boolean variable to flaw) of the flaws..
        std::unordered_map<smt::var, flaw*> in_plan;
        // the current resolver (will be into the trail)..
        resolver* res;
        // the list of resolvers in chronological order..
        std::vector<layer> trail;
#ifndef N_CAUSAL_GRAPH_LISTENERS
        std::vector<causal_graph_listener*> listeners;
#endif
    };
}

#endif /* CAUSAL_GRAPH_H */

