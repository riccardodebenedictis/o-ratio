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
#include "flaw.h"
#include "resolver.h"

causal_graph_java_listener::causal_graph_java_listener(cg::causal_graph& g, JNIEnv * e, jobject o) : causal_graph_listener(g), e(e), o(o) { }

causal_graph_java_listener::~causal_graph_java_listener() { }

void causal_graph_java_listener::flaw_created(const cg::flaw& f) {
    jlong ret_f = reinterpret_cast<jlong> (&f);
    std::vector<cg::resolver*> cs = f.get_causes();
    jlongArray ret_cs = e->NewLongArray(cs.size());
    std::vector<jlong> tmp;
    for (const auto& r : cs) {
        tmp.push_back(reinterpret_cast<jlong> (r));
    }
    e->SetLongArrayRegion(ret_cs, 0, cs.size(), &tmp[0]);
    e->CallVoidMethod(o, e->GetMethodID(e->GetObjectClass(o), "new_flaw", "(J[JLjava/lang/String;)V"), ret_f, ret_cs, "flaw_label");
}

void causal_graph_java_listener::flaw_state_changed(const cg::flaw& f) {
    e->CallVoidMethod(o, e->GetMethodID(e->GetObjectClass(o), "flaw_state_changed", "(J)V"), reinterpret_cast<jlong> (&f));
}

void causal_graph_java_listener::flaw_cost_changed(const cg::flaw& f) {
    e->CallVoidMethod(o, e->GetMethodID(e->GetObjectClass(o), "flaw_cost_changed", "(J)V"), reinterpret_cast<jlong> (&f));
}

void causal_graph_java_listener::current_flaw(const cg::flaw& f) {
    e->CallVoidMethod(o, e->GetMethodID(e->GetObjectClass(o), "current_flaw", "(J)V"), reinterpret_cast<jlong> (&f));
}

void causal_graph_java_listener::resolver_created(const cg::resolver& r) {
    e->CallVoidMethod(o, e->GetMethodID(e->GetObjectClass(o), "new_resolver", "(JJLjava/lang/String;)V"), reinterpret_cast<jlong> (&r), reinterpret_cast<jlong> (&r.get_effect()), "resolver_label");
}

void causal_graph_java_listener::resolver_state_changed(const cg::resolver& r) {
    e->CallVoidMethod(o, e->GetMethodID(e->GetObjectClass(o), "resolver_state_changed", "(J)V"), reinterpret_cast<jlong> (&r));
}

void causal_graph_java_listener::current_resolver(const cg::resolver& r) {
    e->CallVoidMethod(o, e->GetMethodID(e->GetObjectClass(o), "current_resolver", "(J)V"), reinterpret_cast<jlong> (&r));
}

void causal_graph_java_listener::causal_link_added(const cg::flaw& f, const cg::resolver& r) {
    e->CallVoidMethod(o, e->GetMethodID(e->GetObjectClass(o), "new_causal_link", "(JJ)V"), reinterpret_cast<jlong> (&f), reinterpret_cast<jlong> (&r));
}
