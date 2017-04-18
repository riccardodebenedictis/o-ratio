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
 * File:   causal_graph_java_listener.h
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 *
 * Created on April 18, 2017, 7:17 PM
 */

#ifndef CAUSAL_GRAPH_JAVA_LISTENER_H
#define CAUSAL_GRAPH_JAVA_LISTENER_H

#include "causal_graph_listener.h"
#include <jni.h>

class causal_graph_java_listener : public cg::causal_graph_listener {
public:
    causal_graph_java_listener(cg::causal_graph& g, JNIEnv * e, jobject o);
    causal_graph_java_listener(const causal_graph_java_listener& orig) = delete;
    virtual ~causal_graph_java_listener();

private:
    void flaw_created(const cg::flaw& f) override;
    void flaw_state_changed(const cg::flaw& f) override;
    void flaw_cost_changed(const cg::flaw& f) override;
    void current_flaw(const cg::flaw& f) override;
    void resolver_created(const cg::resolver& r) override;
    void resolver_state_changed(const cg::resolver& r) override;
    void current_resolver(const cg::resolver& r) override;
    void causal_link_added(const cg::flaw& f, const cg::resolver& r) override;

private:
    JNIEnv * e;
    jobject o;
};

#endif /* CAUSAL_GRAPH_JAVA_LISTENER_H */

