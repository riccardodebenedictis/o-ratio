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
 * File:   causal_graph_api.cpp
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 * 
 * Created on April 18, 2017, 7:13 PM
 */

#include "causal_graph_api.h"
#include "handle.h"
#include "causal_graph.h"
#include "flaw.h"
#include "resolver.h"
#include "causal_graph_java_listener.h"

jlong Java_it_cnr_istc_ratio_api_CausalGraph_initialise(JNIEnv * e, jobject o, jlong s) {
    return reinterpret_cast<jlong> (new causal_graph_java_listener(*reinterpret_cast<cg::causal_graph*> (s), e, o));
}

void Java_it_cnr_istc_ratio_api_CausalGraph_dispose(JNIEnv * e, jobject o) {
    delete getHandle<causal_graph_java_listener>(e, o);
}