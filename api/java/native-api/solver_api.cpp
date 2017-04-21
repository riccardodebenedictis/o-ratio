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

std::stringstream to_string(std::unordered_map<std::string, ratio::expr> items) {
    std::stringstream ss;
    for (std::unordered_map<std::string, ratio::expr>::iterator is_it = items.begin(); is_it != items.end(); ++is_it) {
        if (is_it != items.begin()) {
            ss << ", ";
        }
        ss << "{ \"name\" = \"" << is_it->first << "\", \"type\" = \"" << is_it->second->t.name << "\", \"value\" = ";
        if (ratio::bool_item * bi = dynamic_cast<ratio::bool_item*> (&*is_it->second)) {
            ss << "{ \"lit\" = \"" << (bi->l.sign ? "b" : "!b") << std::to_string(bi->l.v) << "\", \"value\" = ";
            switch (bi->get_solver().sat.value(bi->l)) {
                case smt::True:
                    ss << "\"True\"";
                    break;
                case smt::False:
                    ss << "\"False\"";
                    break;
                case smt::Undefined:
                    ss << "\"Undefined\"";
                    break;
            }
            ss << " }";
        } else if (ratio::arith_item * ai = dynamic_cast<ratio::arith_item*> (&*is_it->second)) {
            smt::interval bnds = ai->get_solver().la.bounds(ai->l);
            ss << "{ \"lin\" = \"" << ai->l.to_string() << "\" \"val\" = " << std::to_string(ai->get_solver().la.value(ai->l)) << ", \"lb\" = " << std::to_string(bnds.lb) << ", \"ub\" = " << std::to_string(bnds.ub) << " }";
        } else if (ratio::enum_item * ei = dynamic_cast<ratio::enum_item*> (&*is_it->second)) {
            ss << "{ \"var\" = \"e" << std::to_string(ei->ev) << "\", \"vals\" = { ";
            std::unordered_set<smt::set_item*> vals = ei->get_solver().set.value(ei->ev);
            for (std::unordered_set<smt::set_item*>::iterator vals_it = vals.begin(); vals_it != vals.end(); ++vals_it) {
                if (vals_it != vals.begin()) {
                    ss << ", ";
                }
                ss << "\"" << std::to_string(reinterpret_cast<uintptr_t> (*vals_it)) << "\"";
            }
            ss << " } }";
        } else {
            ss << "\"" << std::to_string(reinterpret_cast<uintptr_t> (&*is_it->second)) << "\"";
        }
        ss << " }";
    }
    return ss;
}

std::stringstream to_string(ratio::item* i) {
    std::stringstream ss;
    ss << "{ \"id\" = \"" << std::to_string(reinterpret_cast<uintptr_t> (i)) << "\", \"type\" = \"" << i->t.name << "\"";
    std::unordered_map<std::string, ratio::expr> is = i->get_items();
    if (!is.empty()) {
        ss << ", \"items\" = { " << to_string(is).rdbuf() << " }";
    }
    ss << "}";
    return ss;
}

std::stringstream to_string(ratio::atom* a) {
    std::stringstream ss;
    ss << "{ \"id\" = \"" << std::to_string(reinterpret_cast<uintptr_t> (a)) << "\", \"predicate\" = \"" << a->t.name << "\", \"state\" = [";
    std::unordered_set<smt::set_item*> state_vals = a->get_solver().set.value(a->state);
    for (std::unordered_set<smt::set_item*>::iterator vals_it = state_vals.begin(); vals_it != state_vals.end(); ++vals_it) {
        if (vals_it != state_vals.begin()) {
            ss << ", ";
        }
        if (*vals_it == ratio::atom::active) {
            ss << "Active";
        } else if (*vals_it == ratio::atom::inactive) {
            ss << "Inactive";
        } else if (*vals_it == ratio::atom::unified) {
            ss << "Unified";
        }
    }
    ss << "]";
    std::unordered_map<std::string, ratio::expr> is = a->get_items();
    if (!is.empty()) {
        ss << ", \"pars\" = { " << to_string(is).rdbuf() << " }";
    }
    ss << "}";
    return ss;
}

jlong Java_it_cnr_istc_ratio_api_Solver_initialise(JNIEnv * e, jobject o) {
    return reinterpret_cast<jlong> (new cg::causal_graph());
}

void Java_it_cnr_istc_ratio_api_Solver_dispose(JNIEnv * e, jobject o) {
    delete getHandle<cg::causal_graph>(e, o);
}

jstring Java_it_cnr_istc_ratio_api_Solver_get_1state(JNIEnv * e, jobject o) {
    cg::causal_graph* g = getHandle<cg::causal_graph>(e, o);
    // all the items..
    std::stringstream is;
    // all the atoms..
    std::stringstream as;
    for (const auto& p : g->get_predicates()) {
        std::vector<ratio::expr> atoms = p.second->get_instances();
        for (std::vector<ratio::expr>::iterator as_it = atoms.begin(); as_it != atoms.end(); ++as_it) {
            if (as_it != atoms.begin()) {
                as << ", ";
            }
            std::stringstream a = to_string(static_cast<ratio::atom*> (&**as_it));
            as << a.rdbuf();
        }
    }
    std::queue<ratio::type*> q;
    for (const auto& t : g->get_types()) {
        if (!t.second->primitive) {
            q.push(t.second);
        }
    }
    while (!q.empty()) {
        std::vector<ratio::expr> atoms = q.front()->get_instances();
        for (std::vector<ratio::expr>::iterator is_it = atoms.begin(); is_it != atoms.end(); ++is_it) {
            if (is_it != atoms.begin()) {
                is << ", ";
            }
            std::stringstream i = to_string(static_cast<ratio::item*> (&**is_it));
            is << i.rdbuf();
        }
        for (const auto& p : q.front()->get_predicates()) {
            std::vector<ratio::expr> atoms = p.second->get_instances();
            for (std::vector<ratio::expr>::iterator as_it = atoms.begin(); as_it != atoms.end(); ++as_it) {
                if (as_it != atoms.begin()) {
                    as << ", ";
                }
                std::stringstream a = to_string(static_cast<ratio::atom*> (&**as_it));
                as << a.rdbuf();
            }
        }
        for (const auto& st : q.front()->get_types()) {
            q.push(st.second);
        }
        q.pop();
    }
    // the accessible references..
    std::stringstream rs = to_string(g->get_items());
    std::stringstream ss;
    ss << "{ \"instances\" = [" << is.rdbuf() << "], \"atoms\" = [" << as.rdbuf() << "], \"references\" = {" << rs.rdbuf() << "} }";
    std::string str = ss.str();
    jstring res;
    e->ReleaseStringUTFChars(res, str.c_str());
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