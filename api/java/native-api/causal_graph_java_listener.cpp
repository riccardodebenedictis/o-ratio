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
 * File:   causal_graph_java_listener.cpp
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 * 
 * Created on April 18, 2017, 7:17 PM
 */

#include "causal_graph_java_listener.h"

causal_graph_java_listener::causal_graph_java_listener(cg::causal_graph& g, JNIEnv * e, jobject o) : causal_graph_listener(g), e(e), o(o) { }

causal_graph_java_listener::~causal_graph_java_listener() { }

void causal_graph_java_listener::flaw_created(const cg::flaw& f) { }

void causal_graph_java_listener::flaw_state_changed(const cg::flaw& f) { }

void causal_graph_java_listener::flaw_cost_changed(const cg::flaw& f) { }

void causal_graph_java_listener::current_flaw(const cg::flaw& f) { }

void causal_graph_java_listener::resolver_created(const cg::resolver& r) { }

void causal_graph_java_listener::resolver_state_changed(const cg::resolver& r) { }

void causal_graph_java_listener::current_resolver(const cg::resolver& r) { }

void causal_graph_java_listener::causal_link_added(const cg::flaw& f, const cg::resolver& r) { }