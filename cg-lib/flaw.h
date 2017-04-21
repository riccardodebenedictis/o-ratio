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
 * File:   flaw.h
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 *
 * Created on April 14, 2017, 10:35 AM
 */

#ifndef FLAW_H
#define FLAW_H

#include "la_theory.h"
#include <limits>

namespace cg {

    class causal_graph;
    class resolver;

    class flaw {
        friend class causal_graph;
        friend class resolver;
    public:
        flaw(causal_graph& cg, bool disjunctive = false);
        flaw(const flaw& orig) = delete;
        virtual ~flaw();

        bool is_expanded() const {
            return expanded;
        }

        bool is_initialized() const {
            return initialized;
        }

        smt::var get_in_plan() const {
            return in_plan;
        }

        std::vector<resolver*> get_causes() const {
            return causes;
        }

        double get_cost() const {
            return cost;
        }

    private:
        virtual void init();
        bool expand();
        virtual bool compute_resolvers(std::vector<resolver*>& rs) = 0;
        bool has_subgoals();

    protected:
        causal_graph& g;

    private:
        const bool exclusive;
        bool initialized = false;
        bool expanded = false;
        smt::var in_plan;
        // the resolvers for this flaw..
        std::vector<resolver*> resolvers;
        // the causes for having this flaw..
        std::vector<resolver*> causes;
        // the resolvers supported by this flaw..
        std::vector<resolver*> supports;
        double cost = std::numeric_limits<double>::infinity();
    };
}

#endif /* FLAW_H */

