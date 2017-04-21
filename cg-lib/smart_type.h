/*
 * Copyright (C) 2017 sydde
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
 * File:   smart_type.h
 * Author: Riccardo De Benedictis
 *
 * Created on April 16, 2017, 9.40 AM
 */

#ifndef SMART_TYPE_H
#define SMART_TYPE_H

#include "type.h"
#include "field.h"
#include "causal_graph.h"
#include "sat_value_listener.h"
#include "la_value_listener.h"
#include "set_value_listener.h"

namespace cg {

    class flaw;

    class smart_type : public ratio::type {
    public:

        smart_type(cg::causal_graph& g, scope& s, const std::string& name) : type(g, s, name, false), g(g) { }
        smart_type(const smart_type& that) = delete;

        virtual ~smart_type() { }

        virtual std::vector<flaw*> get_flaws() = 0;

    protected:
        cg::causal_graph& g;
    };

    class atom_listener : public smt::sat_value_listener, public smt::la_value_listener, public smt::set_value_listener {
    public:

        atom_listener(ratio::atom& a) : sat_value_listener(a.get_solver().sat), la_value_listener(a.get_solver().la), set_value_listener(a.get_solver().set), a(a) {
            std::queue<const ratio::type*> q;
            q.push(&a.t);
            while (!q.empty()) {
                for (const auto& f : q.front()->get_fields()) {
                    if (!f.second->synthetic) {
                        ratio::item* i = &*a.get(f.first);
                        if (ratio::bool_item * be = dynamic_cast<ratio::bool_item*> (i)) {
                            listen_sat(be->l.v);
                        } else if (ratio::arith_item * ae = dynamic_cast<ratio::arith_item*> (i)) {
                            for (const auto& term : ae->l.vars) {
                                listen_la(term.first);
                            }
                        } else if (ratio::enum_item * ee = dynamic_cast<ratio::enum_item*> (i)) {
                            listen_set(ee->ev);
                        }
                    }
                }
                for (const auto& st : q.front()->get_supertypes()) {
                    q.push(st);
                }
                q.pop();
            }
        }
        atom_listener(const atom_listener& that) = delete;

        virtual ~atom_listener() { }

    protected:
        ratio::atom& a;
    };
}

#endif /* SMART_TYPE_H */

