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
#include "predicate.h"

jlong Java_it_cnr_istc_ratio_api_Solver_initialise(JNIEnv * e, jobject o) {
    return reinterpret_cast<jlong> (new cg::causal_graph());
}

void Java_it_cnr_istc_ratio_api_Solver_dispose(JNIEnv * e, jobject o) {
    delete getHandle<cg::causal_graph>(e, o);
}

jstring Java_it_cnr_istc_ratio_api_Solver_get_1state(JNIEnv * e, jobject o) {
    cg::causal_graph* g = getHandle<cg::causal_graph>(e, o);
    std::string instances;
    std::string atoms;
    for (const auto& p : g->get_predicates()) {
        for (const auto& e : p.second->get_instances()) {
            atoms += "{ \"id\" = \"" + std::to_string(reinterpret_cast<uintptr_t> (&*e)) + "\"}";
        }
    }
    std::queue<ratio::type*> q;
    for (const auto& t : g->get_types()) {
        if (!t.second->primitive) {
            q.push(t.second);
        }
    }
    while (!q.empty()) {
        for (const auto& e : q.front()->get_instances()) {
            instances += "{ \"id\" = \"" + std::to_string(reinterpret_cast<uintptr_t> (&*e)) + "\"}";
        }
        for (const auto& p : q.front()->get_predicates()) {
            for (const auto& e : p.second->get_instances()) {
                atoms += "{ \"id\" = \"" + std::to_string(reinterpret_cast<uintptr_t> (&*e)) + "\"}";
            }
        }
        for (const auto& st : q.front()->get_types()) {
            q.push(st.second);
        }
        q.pop();
    }
    std::string references;
    for (const auto& i : g->get_items()) {

    }

    std::string state = "{ \"instances\" = [" + instances + "], \"atoms\" = [" + atoms + "], \"references\" = {" + references + "} }";
    jstring res;
    e->ReleaseStringUTFChars(res, state.c_str());
    return res;
}

jboolean Java_it_cnr_istc_ratio_api_Solver_read__Ljava_lang_String_2(JNIEnv * e, jobject o, jstring s) {
    return getHandle<cg::causal_graph>(e, o)->read(e->GetStringUTFChars(s, NULL));
}

jboolean Java_it_cnr_istc_ratio_api_Solver_read___3Ljava_lang_String_2(JNIEnv * e, jobject o, jobjectArray a) {
    jsize length = e->GetArrayLength(a);
    std::vector<std::string> files;
    for (int i = 0; i < length; i++) {
        files.push_back(e->GetStringUTFChars(static_cast<jstring> (e->GetObjectArrayElement(a, i)), NULL));
    }
    return getHandle<cg::causal_graph>(e, o)->read(files);
}

jboolean Java_it_cnr_istc_ratio_api_Solver_solve(JNIEnv * e, jobject o) {
    return getHandle<cg::causal_graph>(e, o)->solve();
}