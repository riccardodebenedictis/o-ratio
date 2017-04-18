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
 * File:   causal_graph_listener.cpp
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 * 
 * Created on April 18, 2017, 6:34 PM
 */

#include "causal_graph_listener.h"
#include "causal_graph.h"
#include <algorithm>

namespace cg {

    causal_graph_listener::causal_graph_listener(causal_graph& g) : g(g) {
        g.listeners.push_back(this);
    }

    causal_graph_listener::~causal_graph_listener() {
        g.listeners.erase(std::find(g.listeners.begin(), g.listeners.end(), this));
    }

    void causal_graph_listener::new_flaw(const flaw& f) {
        flaw_listeners.insert({&f, new flaw_listener(*this, f)});
        flaw_created(f);
    }

    void causal_graph_listener::new_resolver(const resolver& r) {
        resolver_listeners.insert({&r, new resolver_listener(*this, r)});
        resolver_created(r);
    }

    causal_graph_listener::flaw_listener::flaw_listener(causal_graph_listener& l, const flaw& f) : sat_value_listener(l.get_causal_graph().sat), l(l), f(f) { }

    causal_graph_listener::flaw_listener::~flaw_listener() { }

    void causal_graph_listener::flaw_listener::sat_value_change(smt::var v) {
        l.flaw_state_changed(f);
    }

    causal_graph_listener::resolver_listener::resolver_listener(causal_graph_listener& l, const resolver& r) : sat_value_listener(l.get_causal_graph().sat), l(l), r(r) { }

    causal_graph_listener::resolver_listener::~resolver_listener() { }

    void causal_graph_listener::resolver_listener::sat_value_change(smt::var v) {
        l.resolver_state_changed(r);
    }
}