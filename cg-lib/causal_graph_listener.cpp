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
#include "flaw.h"
#include "resolver.h"
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

    void causal_graph_listener::flaw_created(const flaw& f) {
#ifndef NDEBUG
        std::ofstream graph_file;
        graph_file.open("graph.json");
        graph_file << *this;
        graph_file.close();
#endif
    }

    void causal_graph_listener::flaw_state_changed(const flaw& f) {
#ifndef NDEBUG
        std::ofstream graph_file;
        graph_file.open("graph.json");
        graph_file << *this;
        graph_file.close();
#endif
    }

    void causal_graph_listener::flaw_cost_changed(const flaw& f) {
#ifndef NDEBUG
        std::ofstream graph_file;
        graph_file.open("graph.json");
        graph_file << *this;
        graph_file.close();
#endif
    }

    void causal_graph_listener::current_flaw(const flaw& f) {
#ifndef NDEBUG
        std::ofstream graph_file;
        graph_file.open("graph.json");
        graph_file << *this;
        graph_file.close();
#endif
    }

    void causal_graph_listener::new_resolver(const resolver& r) {
        resolver_listeners.insert({&r, new resolver_listener(*this, r)});
        resolver_created(r);
    }

    void causal_graph_listener::resolver_created(const resolver& r) {
#ifndef NDEBUG
        std::ofstream graph_file;
        graph_file.open("graph.json");
        graph_file << *this;
        graph_file.close();
#endif
    }

    void causal_graph_listener::resolver_state_changed(const resolver& r) {
#ifndef NDEBUG
        std::ofstream graph_file;
        graph_file.open("graph.json");
        graph_file << *this;
        graph_file.close();
#endif
    }

    void causal_graph_listener::current_resolver(const resolver& r) {
#ifndef NDEBUG
        std::ofstream graph_file;
        graph_file.open("graph.json");
        graph_file << *this;
        graph_file.close();
#endif
    }

    std::ostream& operator<<(std::ostream& os, const causal_graph_listener& obj) {
        os << "{ ";
        if (!obj.flaw_listeners.empty()) {
            os << "\"flaws\" : [";
            for (std::unordered_map<const flaw*, causal_graph_listener::flaw_listener*>::const_iterator fs_it = obj.flaw_listeners.begin(); fs_it != obj.flaw_listeners.end(); ++fs_it) {
                if (fs_it != obj.flaw_listeners.begin()) {
                    os << ", ";
                }
                os << "{ \"id\" : \"" << std::to_string(reinterpret_cast<uintptr_t> (fs_it->first)) << "\", \"label\" : \"" << fs_it->first->get_label() << "\", \"in_plan\" : ";
                switch (obj.get_causal_graph().sat.value(fs_it->first->get_in_plan())) {
                    case smt::True:
                        os << "\"True\"";
                        break;
                    case smt::False:
                        os << "\"False\"";
                        break;
                    case smt::Undefined:
                        os << "\"Undefined\"";
                        break;
                    default:
                        break;
                }
                if (fs_it->first->get_cost() < std::numeric_limits<double>::infinity()) {
                    os << ", \"cost\" : " << std::to_string(fs_it->first->get_cost());
                }
                os << " }";
            }
            os << "]";
        }
        if (!obj.resolver_listeners.empty()) {
            if (!obj.flaw_listeners.empty()) {
                os << ", ";
            }
            os << "\"resolvers\" : [";
            for (std::unordered_map<const resolver*, causal_graph_listener::resolver_listener*>::const_iterator rs_it = obj.resolver_listeners.begin(); rs_it != obj.resolver_listeners.end(); ++rs_it) {
                if (rs_it != obj.resolver_listeners.begin()) {
                    os << ", ";
                }
                os << "{ \"id\" : \"" << std::to_string(reinterpret_cast<uintptr_t> (rs_it->first)) << "\", \"label\" : \"" << rs_it->first->get_label() << "\", \"chosen\" : ";
                switch (obj.get_causal_graph().sat.value(rs_it->first->get_chosen())) {
                    case smt::True:
                        os << "\"True\"";
                        break;
                    case smt::False:
                        os << "\"False\"";
                        break;
                    case smt::Undefined:
                        os << "\"Undefined\"";
                        break;
                    default:
                        break;
                }
                if (rs_it->first->get_cost() < std::numeric_limits<double>::infinity()) {
                    os << ", \"cost\" : " << std::to_string(rs_it->first->get_cost());
                }
                os << ", \"solves\" : \"" << std::to_string(reinterpret_cast<uintptr_t> (&rs_it->first->get_effect())) << "\"";
                std::vector<flaw*> pres = rs_it->first->get_preconditions();
                if (!pres.empty()) {
                    os << ", \"preconditions\" : [";
                    for (std::vector<flaw*>::const_iterator cs_it = pres.begin(); cs_it != pres.end(); ++cs_it) {
                        if (cs_it != pres.begin()) {
                            os << ", ";
                        }
                        os << "\"" << std::to_string(reinterpret_cast<uintptr_t> (*cs_it)) << "\"";
                    }
                    os << "]";
                }
                os << " }";
            }
            os << "]";
        }
        os << " }";
        return os;
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