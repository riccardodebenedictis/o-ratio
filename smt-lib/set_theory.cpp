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
 * File:   set_theory.cpp
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 * 
 * Created on April 12, 2017, 6:47 PM
 */

#include "set_theory.h"
#include "sat_core.h"
#include "set_value_listener.h"
#include <cassert>
#include <algorithm>

namespace smt {

    set_theory::set_theory(sat_core& c) : theory(c) { }

    set_theory::~set_theory() { }

    var set_theory::new_var(const std::unordered_set<set_item*>& items) {
        assert(!items.empty());
        var id = assigns.size();
        assigns.push_back(std::unordered_map<set_item*, var>());
        if (items.size() == 1) {
            assigns.back().insert({*items.begin(), TRUE});
        } else {
            std::vector<lit> lits;
            for (const auto& i : items) {
                var bv = c.new_var();
                assigns.back().insert({i, bv});
                lits.push_back(lit(bv, true));
                bind(bv);
                is_contained_in.insert({bv, id});
            }
            bool eo = c.exct_one(lits);
            assert(eo);
        }
        exprs.insert({"e" + std::to_string(id), id});
        return id;
    }

    var set_theory::allows(const var& left, set_item& right) const {
        if (assigns[left].find(&right) != assigns[left].end()) {
            return assigns[left].at(&right);
        } else {
            return FALSE;
        }
    }

    var set_theory::eq(const var& left, const var& right) {
        if (left == right) {
            return TRUE;
        }
        if (left > right) {
            return eq(right, left);
        }
        std::unordered_set<set_item*> intersection;
        for (const auto& v : assigns[left]) {
            if (assigns[right].find(v.first) != assigns[right].end()) {
                intersection.insert(v.first);
            }
        }

        if (intersection.empty()) {
            return FALSE;
        }
        std::string s_expr = "e" + std::to_string(left) + " == " + "e" + std::to_string(right);
        if (exprs.find(s_expr) != exprs.end()) {
            // the expression already exists..
            return exprs.at(s_expr);
        } else {
            // we need to create a new variable..
            var e = c.new_var();
            bool nc;
            for (const auto& v : assigns[left]) {
                if (intersection.find(v.first) == intersection.end()) {
                    nc = c.new_clause({lit(e, false), lit(v.second, false)});
                    assert(nc);
                }
            }
            for (const auto& v : assigns[right]) {
                if (intersection.find(v.first) == intersection.end()) {
                    nc = c.new_clause({lit(e, false), lit(v.second, false)});
                    assert(nc);
                }
            }
            for (const auto& v : intersection) {
                nc = c.new_clause({lit(e, false), lit(assigns[left].at(v), false), lit(assigns[right].at(v), true)});
                assert(nc);
                nc = c.new_clause({lit(e, false), lit(assigns[left].at(v), true), lit(assigns[right].at(v), false)});
                assert(nc);
                nc = c.new_clause({lit(e, true), lit(assigns[left].at(v), false), lit(assigns[right].at(v), false)});
                assert(nc);
            }
            exprs.insert({s_expr, e});
            return e;
        }
    }

    std::unordered_set<set_item*> set_theory::value(var v) const {
        std::unordered_set<set_item*> vals;
        for (const auto& v : assigns[v]) {
            if (c.value(v.second) != False) {
                vals.insert(v.first);
            }
        }
        return vals;
    }

    bool set_theory::propagate(const lit& p, std::vector<lit>& confl) {
        var set_var = is_contained_in[p.v];
        if (listening.find(set_var) != listening.end()) {
            for (const auto& l : listening[set_var]) {
                l->set_value_change(set_var);
            }
        }
        return true;
    }

    bool set_theory::check(std::vector<lit>& confl) {
        return true;
    }

    void set_theory::push() {
        layers.push_back(layer());
    }

    void set_theory::pop() {
        for (const auto& v : layers.back().vars) {
            if (listening.find(v) != listening.end()) {
                for (const auto& l : listening[v]) {
                    l->set_value_change(v);
                }
            }
        }
        layers.pop_back();
    }

    void set_theory::listen(var v, set_value_listener * const l) {
        listening[v].push_back(l);
    }

    void set_theory::forget(var v, set_value_listener * const l) {
        listening.at(v).erase(std::find(listening.at(v).begin(), listening.at(v).end(), l));
        if (listening.at(v).empty()) {
            listening.erase(v);
        }
    }
}