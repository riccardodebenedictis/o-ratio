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
 * File:   causal_graph_listener.h
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 *
 * Created on April 18, 2017, 3:45 PM
 */

#ifndef CAUSAL_GRAPH_LISTENER_H
#define CAUSAL_GRAPH_LISTENER_H

#include "causal_graph.h"

namespace cg {

    class causal_graph_listener {
    public:

        causal_graph_listener(causal_graph& g) : g(g) {
            g.listeners.push_back(this);
        }
        causal_graph_listener(const causal_graph_listener& that) = delete;

        virtual ~causal_graph_listener() {
            g.listeners.erase(std::find(g.listeners.begin(), g.listeners.end(), this));
        }

        virtual void new_flaw(const flaw& f) { }

        virtual void updated_flaw(const flaw& f) { }

        virtual void new_resolver(const resolver& r) { }

        virtual void updated_resolver(const resolver& r) { }

        virtual void current_flaw(const flaw& f) { }

        virtual void current_resolver(const resolver& r) { }

    protected:
        causal_graph& g;
    };
}

#endif /* CAUSAL_GRAPH_LISTENER_H */

