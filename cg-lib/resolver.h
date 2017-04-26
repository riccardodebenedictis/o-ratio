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
 * File:   resolver.h
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 *
 * Created on April 14, 2017, 10:35 AM
 */

#ifndef RESOLVER_H
#define RESOLVER_H

#include "la_theory.h"

namespace cg {

    class causal_graph;
    class flaw;

    class resolver {
        friend class causal_graph;
        friend class flaw;
    public:
        resolver(causal_graph& g, const smt::lin& cost, flaw& e);
        resolver(const resolver& orig) = delete;
        virtual ~resolver();

        virtual bool apply() = 0;

        smt::var get_chosen() const {
            return chosen;
        }

        flaw& get_effect() const {
            return effect;
        }

        std::vector<flaw*> get_preconditions() const {
            return preconditions;
        }
        double get_cost() const;

        virtual std::string get_label() const;

    protected:
        causal_graph& g;
        smt::var chosen;
        smt::lin cost;
        // the preconditions of this resolver..
        std::vector<flaw*> preconditions;
        // the flaw solved by this resolver..
        flaw& effect;
    };
}

#endif /* RESOLVER_H */

