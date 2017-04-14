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
 * File:   solver_api.cpp
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 * 
 * Created on April 14, 2017, 4:47 PM
 */

#include "solver_api.h"
#include "handle.h"
#include "causal_graph.h"

jboolean Java_it_cnr_istc_ratio_api_Solver_read__Ljava_lang_String_2(JNIEnv * e, jobject o, jstring s) { }

jboolean Java_it_cnr_istc_ratio_api_Solver_read__Ljava_util_Collection_2(JNIEnv * e, jobject o, jobject s) { }

jboolean Java_it_cnr_istc_ratio_api_Solver_solve(JNIEnv * e, jobject o) { }

void Java_it_cnr_istc_ratio_api_Solver_initialise(JNIEnv * e, jobject o) {
    std::cout << "initializing solver.." << std::endl;
    cg::causal_graph* g = new cg::causal_graph();
    setHandle(e, o, g);
}

void Java_it_cnr_istc_ratio_api_Solver_dispose(JNIEnv * e, jobject o) {
    std::cout << "clearing solver.." << std::endl;
    cg::causal_graph* g = getHandle<cg::causal_graph>(e, o);
    delete g;
}