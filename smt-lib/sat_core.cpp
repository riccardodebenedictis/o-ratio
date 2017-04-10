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
 * File:   sat_core.cpp
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 * 
 * Created on April 10, 2017, 11:43 AM
 */

#include "sat_core.h"
#include "clause.h"
#include "theory.h"
#include <cassert>
#include <algorithm>

namespace smt {

    sat_core::sat_core() {
        var c_false = new_var();
        var c_true = new_var();
        assert(c_false == FALSE);
        assert(c_true == TRUE);
        assigns[FALSE] = False;
        assigns[TRUE] = True;
        level[FALSE] = 0;
        level[TRUE] = 0;
    }

    sat_core::~sat_core() {
        for (const auto& l : bounds) {
            for (const auto& vl : l.second) {
                delete vl;
            }
        }
        for (const auto& th : theories) {
            delete th;
        }
        for (const auto& c : constrs) {
            delete c;
        }
    }

    var sat_core::new_var() {
        var id = assigns.size();
        watches.push_back(std::vector<constr*>());
        watches.push_back(std::vector<constr*>());
        assigns.push_back(Undefined);
        level.push_back(0);
        reason.push_back(nullptr);
        return id;
    }

    bool sat_core::new_clause(const std::vector<lit>& lits) {
        assert(root_level());
        if (std::any_of(lits.begin(), lits.end(), [&](const lit & p) {
                return value(p) == True;
            })) {
        return true;
    } else if (std::all_of(lits.begin(), lits.end(), [&](const lit & p) {
                return value(p) == False;
            })) {
        return false;
    } else {
            std::vector<lit> c_lits;
            std::copy_if(lits.begin(), lits.end(), std::back_inserter(c_lits), [&](const lit & p) {
                return value(p) == Undefined; });
            if (c_lits.size() == 1) {
                enqueue(c_lits[0]);
            } else {
                constrs.push_back(new clause(*this, c_lits));
            }
            return true;
        }
    }

    constr* sat_core::propagate() {
        while (!prop_q.empty()) {
            // we propagate sat constraints..
            std::vector<constr*> tmp = std::move(watches[index(prop_q.front())]);
            for (size_t i = 0; i < tmp.size(); i++) {
                if (!tmp[i]->propagate(prop_q.front())) {
                    for (size_t j = i + 1; j < tmp.size(); j++) {
                        watches[index(prop_q.front())].push_back(tmp[j]);
                    }
#ifndef NDEBUG
                    std::vector<lit> args = tmp[i]->args();
                    assert(std::count_if(args.begin(), args.end(), [&](const lit & p) {
                        return std::find(watches[index(!p)].begin(), watches[index(!p)].end(), tmp[i]) != watches[index(!p)].end();
                    }) == 2);
#endif
                    while (!prop_q.empty()) {
                        prop_q.pop();
                    }
                    return tmp[i];
                }
#ifndef NDEBUG
                std::vector<lit> args = tmp[i]->args();
                assert(std::count_if(args.begin(), args.end(), [&](const lit & p) {
                    return std::find(watches[index(!p)].begin(), watches[index(!p)].end(), tmp[i]) != watches[index(!p)].end(); }) == 2);
#endif
            }

            // we perform theory propagation..
            for (const auto& th : theories) {
                constr* conflict = th->propagate(prop_q.front());
                if (conflict) {
                    return conflict;
                }
            }


            prop_q.pop();
        }

        // we check theories..
        for (const auto& th : theories) {
            constr* conflict = th->check();
            if (conflict) {
                return conflict;
            }
        }

        return nullptr;
    }

    bool sat_core::enqueue(const lit& p, constr * const c) {
        switch (value(p)) {
            case True:
                return true;
            case False:
                return false;
            case Undefined:
                assigns[p.v] = p.sign ? True : False;
                level[p.v] = trail_lim.size();
                reason[p.v] = c;
                trail.push_back(p);
                prop_q.push(p);
                return true;
            default:
                std::unexpected();
        }
    }

    void sat_core::analyze(const constr& confl, std::vector<lit>& out_learnt, size_t& out_btlevel) {
        out_learnt.push_back(lit(0, false));
        out_btlevel = 0;
        std::set<var> seen;
        size_t counter = 0;
        lit p = trail_lim.back();
        const constr* p_reason = &confl;
        do {
            for (const auto& q : p_reason->lits) {
                if (p.v != q.v && seen.find(q.v) == seen.end()) {
                    seen.insert(q.v);
                    if (level[q.v] == trail_lim.size()) {
                        counter++;
                    } else if (level[q.v] > 0) {
                        out_learnt.push_back(!q);
                        out_btlevel = std::max(out_btlevel, level[q.v]);
                    }
                }
            }
            do {
                p = trail.back();
                p_reason = reason[p.v];
                pop_one();
            } while (seen.find(p.v) == seen.end());
            counter--;
        } while (counter > 0);
        out_learnt[0] = !p;
    }

    bool sat_core::assume(const lit& p) {
        trail_lim.push_back(p);
        for (const auto& th : theories) {
            th->push();
        }
        return enqueue(p);
    }

    bool sat_core::check() {
        while (true) {
            constr* cnfl = propagate();
            if (cnfl) {
                if (root_level()) {
                    return false;
                }
                std::vector<lit> no_good;
                size_t bt_level;
                analyze(*cnfl, no_good, bt_level);
                while (trail_lim.size() > bt_level) {
                    pop();
                }
                record(no_good);
            } else {
                return true;
            }
        }
    }

    void sat_core::pop() {
        while (trail_lim.back() != trail.back()) {
            pop_one();
        }
        pop_one();
        trail_lim.pop_back();
        for (const auto& th : theories) {
            th->pop();
        }
    }

    void sat_core::pop_one() {
        assigns[trail.back().v] = Undefined;
        reason[trail.back().v] = nullptr;
        level[trail.back().v] = 0;
        trail.pop_back();
    }

    void sat_core::record(const std::vector<lit>& lits) {
#ifndef NDEBUG
        unsigned undefs = std::count_if(lits.begin(), lits.end(), [&](const lit & p) {
            return value(p) == Undefined; });
        unsigned falses = std::count_if(lits.begin(), lits.end(), [&](const lit & p) {
            return value(p) == False; });
        assert(undefs == 1);
        assert(falses == lits.size() - 1);
        assert(value(lits[0]) != Undefined);
#endif
        if (lits.size() == 1) {
            assert(root_level());
            bool e = enqueue(lits[0]);
            assert(e);
        } else {
            constrs.push_back(new clause(*this, lits));
            bool e = enqueue(lits[0]);
            assert(e);
        }
    }

    void sat_core::add_theory(theory & th) {
        theories.push_back(&th);
    }

    void sat_core::remove_theory(theory & th) {
        const auto& it = std::find(theories.begin(), theories.end(), &th);
        if (it != theories.end()) {
            theories.erase(it);
            for (const auto& lo : th.listening_on) {
                unbind(lo, th);
            }
            th.listening_on.clear();
        }
    }

    void sat_core::bind(var v, theory & th) {
        bounds[v].push_back(&th);
    }

    void sat_core::unbind(var v, theory & th) {
        const auto& it = std::find(bounds[v].begin(), bounds[v].end(), &th);
        if (it != bounds[v].end()) {
            bounds[v].erase(it);
        }
    }

    std::ostream& operator<<(std::ostream& os, const sat_core & obj) {
        os << "**********[sat core]************" << std::endl;
        for (size_t i = 0; i < obj.assigns.size(); i++) {
            os << "b" << std::to_string(i) << ": ";
            switch (obj.value(i)) {
                case True:
                    os << "T";
                    if (obj.level[i] > 0) {
                        os << " (" << std::to_string(obj.level[i]) << ")";
                    }
                    break;
                case False:
                    os << "F";
                    if (obj.level[i] > 0) {
                        os << " (" << std::to_string(obj.level[i]) << ")";
                    }
                    break;
                case Undefined:
                    break;
                default:
                    break;
            }
            os << std::endl;
        }
        for (const auto& c : obj.constrs) {
            os << *c << std::endl;
        }
        os << "********************************" << std::endl;
        return os;
    }
}