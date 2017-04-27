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
 * File:   la_theory.cpp
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 * 
 * Created on April 11, 2017, 11:14 AM
 */

#include "la_theory.h"
#include "sat_core.h"
#include "la_value_listener.h"
#include <cassert>
#include <algorithm>

namespace smt {

    la_theory::la_theory(sat_core& c) : theory(c) { }

    la_theory::~la_theory() { }

    var la_theory::new_var() {
        var id = assigns.size();
        assigns.push_back(interval());
        vals.push_back(0);
        exprs.insert({"x" + std::to_string(id), id});
        a_watches.push_back(std::vector<assertion*>());
        t_watches.push_back(std::set<t_row*>());
        return id;
    }

    var la_theory::leq(const lin& left, const lin& right) {
        lin expr = left - right;
        std::vector<var> vars;
        for (const auto& term : expr.vars) {
            vars.push_back(term.first);
        }
        for (const auto& v : vars) {
            if (tableau.find(v) != tableau.end()) {
                double c = expr.vars[v];
                expr.vars.erase(v);
                expr += tableau[v]->l * c;
            }
        }

        double c_right = -expr.known_term;
        expr.known_term = 0;
        interval i = bounds(expr);
        if (i <= c_right) {
            // the constraint is already satisfied..
            return TRUE;
        } else if (i > c_right) {
            // the constraint is unsatisfable..
            return FALSE;
        } else {
            var slack = mk_slack(expr);
            std::string s_assertion = "x" + std::to_string(slack) + " <= " + std::to_string(c_right);
            if (s_asrts.find(s_assertion) != s_asrts.end()) {
                // this assertion already exists..
                return s_asrts.at(s_assertion);
            } else {
                var ctr = c.new_var();
                bind(ctr);
                s_asrts.insert({s_assertion, ctr});
                assertion* a = new assertion(*this, op::leq, ctr, slack, c_right);
                v_asrts.insert({ctr, a});
                a_watches[slack].push_back(a);
                return ctr;
            }
        }
    }

    var la_theory::geq(const lin& left, const lin& right) {
        lin expr = left - right;
        std::vector<var> vars;
        for (const auto& term : expr.vars) {
            vars.push_back(term.first);
        }
        for (const auto& v : vars) {
            if (tableau.find(v) != tableau.end()) {
                double c = expr.vars[v];
                expr.vars.erase(v);
                expr += tableau[v]->l * c;
            }
        }

        double c_right = -expr.known_term;
        expr.known_term = 0;
        interval i = bounds(expr);
        if (i >= c_right) {
            // the constraint is already satisfied..
            return TRUE;
        } else if (i < c_right) {
            // the constraint is unsatisfable..
            return FALSE;
        } else {
            var slack = mk_slack(expr);
            std::string s_assertion = "x" + std::to_string(slack) + " >= " + std::to_string(c_right);
            if (s_asrts.find(s_assertion) != s_asrts.end()) {
                // this assertion already exists..
                return s_asrts.at(s_assertion);
            } else {
                var ctr = c.new_var();
                bind(ctr);
                s_asrts.insert({s_assertion, ctr});
                assertion* a = new assertion(*this, op::geq, ctr, slack, c_right);
                v_asrts.insert({ctr, a});
                a_watches[slack].push_back(a);
                return ctr;
            }
        }
    }

    var la_theory::mk_slack(const lin& l) {
        std::string s_expr = l.to_string();
        var slack;
        if (exprs.find(s_expr) != exprs.end()) {
            // the expression already exists..
            slack = exprs.at(s_expr);
        } else {
            // we need to create a new slack variable..
            slack = new_var();
            exprs.insert({s_expr, slack});
            // we set the initial bounds of the new slack variable..
            assigns[slack] = bounds(l);
            // we set the initial value of the new slack variable..
            vals[slack] = value(l);
            t_row* row = new t_row(*this, slack, l);
            // we add a new row into the tableau..
            tableau.insert({slack, row});
            for (const auto& term : row->l.vars) {
                t_watches[term.first].insert(row);
            }
        }
        return slack;
    }

    constr* la_theory::propagate(const lit& p) {
        assertion* a = v_asrts.at(p.v);
        constr* cnfl = nullptr;
        switch (a->o) {
            case op::leq:
                if (p.sign) {
                    cnfl = assert_upper(a->x, a->v, p);
                    if (cnfl) return cnfl;
                } else {
                    cnfl = assert_lower(a->x, a->v, p);
                    if (cnfl) return cnfl;
                }
                break;
            case op::geq:
                if (p.sign) {
                    cnfl = assert_lower(a->x, a->v, p);
                    if (cnfl) return cnfl;
                } else {
                    cnfl = assert_upper(a->x, a->v, p);
                    if (cnfl) return cnfl;
                }
                break;
            default:
                break;
        }
        return cnfl;
    }

    constr* la_theory::check() {
        while (true) {
            auto x_i_it = std::find_if(tableau.begin(), tableau.end(), [&](const std::pair<var, t_row*>& v) {
                return vals[v.first] < assigns[v.first].lb || vals[v.first] > assigns[v.first].ub; });
            if (x_i_it == tableau.end()) {
                return nullptr;
            }
            // the current value of the x_i variable is out of its bounds..
            var x_i = (*x_i_it).first;
            // the flawed row..
            t_row* f_row = (*x_i_it).second;
            if (vals[x_i] < assigns[x_i].lb) {
                auto x_j_it = std::find_if(f_row->l.vars.begin(), f_row->l.vars.end(), [&](const std::pair<var, double>& v) {
                    return (f_row->l.vars.at(v.first) > 0 && vals[v.first] < assigns[v.first].ub) || (f_row->l.vars.at(v.first) < 0 && vals[v.first] > assigns[v.first].lb); });
                if (x_j_it != f_row->l.vars.end()) {
                    // var x_j can be used to increase the value of x_i..
                    pivot_and_update(x_i, (*x_j_it).first, assigns[x_i].lb);
                } else {
                    // we generate an explanation for the conflict..
                    std::vector<lit> expl;
                    for (auto& term : f_row->l.vars) {
                        if (term.second > 0) {
                            expl.push_back(lit(s_asrts.at("x" + std::to_string(term.first) + " <= " + std::to_string(assigns[term.first].ub)), false));
                        } else if (term.second < 0) {
                            expl.push_back(lit(s_asrts.at("x" + std::to_string(term.first) + " >= " + std::to_string(assigns[term.first].lb)), false));
                        }
                    }
                    expl.push_back(lit(s_asrts.at("x" + std::to_string(x_i) + " >= " + std::to_string(assigns[x_i].lb)), false));
                    return new constr(c, expl);
                }
            } else if (vals[x_i] > assigns[x_i].ub) {
                auto x_j_it = std::find_if(f_row->l.vars.begin(), f_row->l.vars.end(), [&](const std::pair<var, double>& v) {
                    return (f_row->l.vars[v.first] < 0 && vals[v.first] < assigns[v.first].ub) || (f_row->l.vars[v.first] > 0 && vals[v.first] > assigns[v.first].lb); });
                if (x_j_it != f_row->l.vars.end()) {
                    // var x_j can be used to decrease the value of x_i..
                    pivot_and_update(x_i, (*x_j_it).first, assigns[x_i].ub);
                } else {
                    // we generate an explanation for the conflict..
                    std::vector<lit> expl;
                    for (auto& term : f_row->l.vars) {
                        if (term.second > 0) {
                            expl.push_back(lit(s_asrts.at("x" + std::to_string(term.first) + " >= " + std::to_string(assigns[term.first].lb)), false));
                        } else if (term.second < 0) {
                            expl.push_back(lit(s_asrts.at("x" + std::to_string(term.first) + " <= " + std::to_string(assigns[term.first].ub)), false));
                        }
                    }
                    expl.push_back(lit(s_asrts.at("x" + std::to_string(x_i) + " <= " + std::to_string(assigns[x_i].ub)), false));
                    return new constr(c, expl);
                }
            }
        }
    }

    void la_theory::push() {
        layers.push_back(layer());
    }

    void la_theory::pop() {
        // we restore the variables' bounds..
        for (const auto& lb : layers.back().lbs) {
            assigns[lb.first].lb = lb.second;
        }
        for (const auto& ub : layers.back().ubs) {
            assigns[ub.first].ub = ub.second;
        }
        layers.pop_back();
    }

    constr* la_theory::assert_lower(var x_i, double val, const lit& p) {
        if (val <= assigns[x_i].lb) {
            return nullptr;
        } else if (val > assigns[x_i].ub) {
            return new constr(c,{!p, lit(s_asrts["x" + std::to_string(x_i) + " <= " + std::to_string(assigns[x_i].ub)], false)});
        } else {
            if (!layers.empty()) {
                if (layers.back().lbs.find(x_i) == layers.back().lbs.end()) {
                    layers.back().lbs.insert({x_i, assigns[x_i].lb});
                }
            }
            assigns[x_i].lb = val;
            if (vals[x_i] < val) {
                if (tableau.find(x_i) == tableau.end()) {
                    update(x_i, val);
                }
            }

            constr* cnfl = nullptr;
            // unate propagation..
            for (const auto& c : a_watches[x_i]) {
                cnfl = c->propagate_lb(x_i);
                if (cnfl) return cnfl;
            }
            // bound propagation..
            for (const auto& c : t_watches[x_i]) {
                cnfl = c->propagate_lb(x_i);
                if (cnfl) return cnfl;
            }

            return cnfl;
        }
    }

    constr* la_theory::assert_upper(var x_i, double val, const lit& p) {
        if (val >= assigns[x_i].ub) {
            return nullptr;
        } else if (val < assigns[x_i].lb) {
            return new constr(c,{!p, lit(s_asrts["x" + std::to_string(x_i) + " >= " + std::to_string(assigns[x_i].lb)], false)});
        } else {
            if (!layers.empty()) {
                if (layers.back().ubs.find(x_i) == layers.back().ubs.end()) {
                    layers.back().ubs.insert({x_i, assigns[x_i].ub});
                }
            }
            assigns[x_i].ub = val;
            if (vals[x_i] > val) {
                if (tableau.find(x_i) == tableau.end()) {
                    update(x_i, val);
                }
            }

            constr* cnfl = nullptr;
            // unate propagation..
            for (const auto& c : a_watches[x_i]) {
                cnfl = c->propagate_ub(x_i);
                if (cnfl) return cnfl;
            }
            // bound propagation..
            for (const auto& c : t_watches[x_i]) {
                cnfl = c->propagate_ub(x_i);
                if (cnfl) return cnfl;
            }

            return cnfl;
        }
    }

    void la_theory::update(var x_i, double v) {
        assert(tableau.find(x_i) == tableau.end() && "x_i should be a non-basic variable..");
        for (const auto& c : t_watches[x_i]) {
            // x_j = x_j + a_ji(v - x_i)..
            vals[c->x] += c->l.vars[x_i] * (v - vals[x_i]);
            if (listening.find(c->x) != listening.end()) {
                for (const auto& l : listening[c->x]) {
                    l->la_value_change(c->x);
                }
            }
        }
        // x_i = v..
        vals[x_i] = v;
        if (listening.find(x_i) != listening.end()) {
            for (const auto& l : listening[x_i]) {
                l->la_value_change(x_i);
            }
        }
    }

    void la_theory::pivot_and_update(var x_i, var x_j, double v) {
        assert(tableau.find(x_i) != tableau.end() && "x_i should be a basic variable..");
        assert(tableau.find(x_j) == tableau.end() && "x_j should be a non-basic variable..");
        assert(tableau[x_i]->l.vars.find(x_j) != tableau[x_i]->l.vars.end());

        double theta = (v - vals[x_i]) / tableau.at(x_i)->l.vars.at(x_j);
        // x_i = v
        vals[x_i] = v;
        if (listening.find(x_i) != listening.end()) {
            for (const auto& l : listening[x_i]) {
                l->la_value_change(x_i);
            }
        }
        // x_j = x_j + theta
        vals[x_j] += theta;
        if (listening.find(x_j) != listening.end()) {
            for (const auto& l : listening[x_j]) {
                l->la_value_change(x_j);
            }
        }
        for (const auto& c : t_watches[x_j]) {
            if (c->x != x_i) {
                // x_k = x_k + a_kj * theta..
                vals[c->x] += c->l.vars[x_j] * theta;
                if (listening.find(c->x) != listening.end()) {
                    for (const auto& l : listening[c->x]) {
                        l->la_value_change(c->x);
                    }
                }
            }
        }

        pivot(x_i, x_j);
    }

    void la_theory::pivot(var x_i, var x_j) {
        // the exiting row..
        t_row* ex_row = tableau.at(x_i);
        for (const auto& c : ex_row->l.vars) {
            t_watches[c.first].erase(ex_row);
        }
        tableau.erase(x_i);

        lin expr = ex_row->l;
        double c = expr.vars.at(x_j);
        expr.vars.erase(x_j);
        expr /= -c;
        expr.vars.insert({x_i, 1 / c});

        std::vector<t_row*> rows;
        for (const auto& c : t_watches[x_j]) {
            rows.push_back(c);
        }
        for (const auto& r : rows) {
            for (const auto& term : r->l.vars) {
                t_watches[term.first].erase(r);
            }
            double cc = r->l.vars.at(x_j);
            r->l.vars.erase(x_j);
            r->l += expr*cc;
            for (const auto& term : r->l.vars) {
                t_watches[term.first].insert(r);
            }
        }
        delete ex_row;

        t_row* row = new t_row(*this, x_j, expr);
        // we add a new row into the tableau..
        tableau.insert({x_j, row});
        for (const auto& term : row->l.vars) {
            t_watches[term.first].insert(row);
        }
    }

    void la_theory::listen(var v, la_value_listener * const l) {
        listening[v].push_back(l);
    }

    void la_theory::forget(var v, la_value_listener * const l) {
        listening.at(v).erase(std::find(listening.at(v).begin(), listening.at(v).end(), l));
        if (listening.at(v).empty()) {
            listening.erase(v);
        }
    }

    std::ostream& operator<<(std::ostream& os, const la_theory& obj) {
        os << "**********[la_theory]***********" << std::endl;
        for (size_t i = 0; i < obj.assigns.size(); i++) {
            os << "x" << std::to_string(i) << ": " << obj.assigns[i] << " (" << std::to_string(obj.vals[i]) << ")" << std::endl;
        }
        for (const auto& asrt : obj.v_asrts) {
            os << *asrt.second << std::endl;
        }
        for (const auto& row : obj.tableau) {
            os << *row.second << std::endl;
        }
        os << "********************************" << std::endl;
        return os;
    }

    assertion::assertion(la_theory& th, op o, var b, var x, double v) : th(th), o(o), b(b), x(x), v(v) { }

    assertion::~assertion() { }

    constr* assertion::propagate_lb(var x) {
        if (th.assigns[x].lb > v) {
            lit p = lit(th.s_asrts["x" + std::to_string(x) + " >= " + std::to_string(th.assigns[x].lb)], false);
            switch (o) {
                case leq:
                    // [x >= lb(x)] -> ![x <= v]..
                    // the assertion is unsatisfable..
                    switch (th.c.value(b)) {
                        case True:
                            // we have a propositional inconsistency..
                            return new constr(th.c,{p, lit(b, false)});
                        case False:
                            // nothing to propagate..
                            break;
                        case Undefined:
                            // we propagate information to the sat core..
                            th.record({lit(b, false), p});
                            break;
                        default:
                            break;
                    }
                    break;
                case geq:
                    // [x >= lb(x)] -> [x >= v]..
                    // the assertion is satisfied..
                    switch (th.c.value(b)) {
                        case True:
                            // nothing to propagate..
                            break;
                        case False:
                            // we have a propositional inconsistency..
                            return new constr(th.c,{p, lit(b, true)});
                        case Undefined:
                            // we propagate information to the sat core..
                            th.record({lit(b, true), p});
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
        }
        return nullptr;
    }

    constr* assertion::propagate_ub(var x) {
        if (th.assigns[x].ub < v) {
            lit p = lit(th.s_asrts["x" + std::to_string(x) + " <= " + std::to_string(th.assigns[x].ub)], false);
            switch (o) {
                case leq:
                    // [x <= ub(x)] -> [x <= v]..
                    // the assertion is satisfied..
                    switch (th.c.value(b)) {
                        case True:
                            // nothing to propagate..
                            break;
                        case False:
                            // we have a propositional inconsistency..
                            return new constr(th.c,{p, lit(b, true)});
                            break;
                        case Undefined:
                            // we propagate information to the sat core..
                            th.record({lit(b, true), p});
                            break;
                        default:
                            break;
                    }
                    break;
                case geq:
                    // [x <= ub(x)] -> ![x >= v]..
                    // the assertion is unsatisfable..
                    switch (th.c.value(b)) {
                        case True:
                            // we have a propositional inconsistency..
                            return new constr(th.c,{p, lit(b, false)});
                            break;
                        case False:
                            // nothing to propagate..
                            break;
                        case Undefined:
                            // we propagate information to the sat core..
                            th.record({lit(b, false), p});
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
        }
        return nullptr;
    }

    std::ostream& operator<<(std::ostream& os, const assertion& obj) {
        os << "b" << std::to_string(obj.b);
        switch (obj.th.get_core().value(obj.b)) {
            case True:
                os << "(T)";
                break;
            case False:
                os << "(F)";
                break;
            case Undefined:
                os << "(U)";
                break;
            default:
                break;
        }
        os << " x" << std::to_string(obj.x);
        switch (obj.o) {
            case leq:
                os << " <= ";
                break;
            case geq:
                os << " >= ";
                break;
            default:
                break;
        }
        os << std::to_string(obj.v);
        return os;
    }

    t_row::t_row(la_theory& th, var x, lin l) : th(th), x(x), l(l) { }

    t_row::~t_row() { }

    constr* t_row::propagate_lb(var x) {
        if (l.vars.at(x) > 0) {
            double lb;
            std::vector<lit> expl;
            for (const auto& term : l.vars) {
                if (term.second > 0) {
                    if (th.bounds(term.first).lb > -std::numeric_limits<double>::infinity()) {
                        // nothing to propagate..
                        return nullptr;
                    } else {
                        lb += term.second * th.bounds(term.first).lb;
                        expl.push_back(lit(th.s_asrts["x" + std::to_string(term.first) + " >= " + std::to_string(th.assigns[term.first].lb)], false));
                    }
                } else if (term.second < 0) {
                    if (th.bounds(term.first).ub < std::numeric_limits<double>::infinity()) {
                        // nothing to propagate..
                        return nullptr;
                    } else {
                        lb += term.second * th.bounds(term.first).ub;
                        expl.push_back(lit(th.s_asrts["x" + std::to_string(term.first) + " <= " + std::to_string(th.assigns[term.first].ub)], false));
                    }
                }
            }
            if (lb > th.bounds(x).lb) {
                for (const auto& c : th.a_watches[x]) {
                    if (lb > c->v) {
                        std::vector<lit> c_expl = expl;
                        switch (c->o) {
                            case leq:
                                c_expl.push_back(lit(c->b, false));
                                // the assertion is unsatisfable..
                                switch (th.c.value(c->b)) {
                                    case True:
                                        // we have a propositional inconsistency..
                                        return new constr(th.c, c_expl);
                                        break;
                                    case False:
                                        // nothing to propagate..
                                        break;
                                    case Undefined:
                                        // we propagate information to the sat core..
                                        th.record(c_expl);
                                        break;
                                    default:
                                        break;
                                }
                                break;
                            case geq:
                                c_expl.push_back(lit(c->b, true));
                                // the assertion is satisfied..
                                switch (th.c.value(c->b)) {
                                    case True:
                                        // nothing to propagate..
                                        break;
                                    case False:
                                        // we have a propositional inconsistency..
                                        return new constr(th.c, c_expl);
                                        break;
                                    case Undefined:
                                        // we propagate information to the sat core..
                                        th.record(c_expl);
                                        break;
                                    default:
                                        break;
                                }
                                break;
                            default:
                                break;
                        }
                    }
                }
            }
        } else {
            double ub;
            std::vector<lit> expl;
            for (const auto& term : l.vars) {
                if (term.second > 0) {
                    if (th.bounds(term.first).ub < std::numeric_limits<double>::infinity()) {
                        // nothing to propagate..
                        return nullptr;
                    } else {
                        ub += term.second * th.bounds(term.first).ub;
                        expl.push_back(lit(th.s_asrts["x" + std::to_string(term.first) + " <= " + std::to_string(th.assigns[term.first].ub)], false));
                    }
                } else if (term.second < 0) {
                    if (th.bounds(term.first).lb > -std::numeric_limits<double>::infinity()) {
                        // nothing to propagate..
                        return nullptr;
                    } else {
                        ub += term.second * th.bounds(term.first).lb;
                        expl.push_back(lit(th.s_asrts["x" + std::to_string(term.first) + " >= " + std::to_string(th.assigns[term.first].lb)], false));
                    }
                }
            }
            if (ub < th.bounds(x).ub) {
                for (const auto& c : th.a_watches[x]) {
                    if (ub > c->v) {
                        std::vector<lit> c_expl = expl;
                        switch (c->o) {
                            case leq:
                                c_expl.push_back(lit(c->b, false));
                                // the assertion is unsatisfable..
                                switch (th.c.value(c->b)) {
                                    case True:
                                        // we have a propositional inconsistency..
                                        return new constr(th.c, c_expl);
                                        break;
                                    case False:
                                        // nothing to propagate..
                                        break;
                                    case Undefined:
                                        // we propagate information to the sat core..
                                        th.record(c_expl);
                                        break;
                                    default:
                                        break;
                                }
                                break;
                            case geq:
                                c_expl.push_back(lit(c->b, true));
                                // the assertion is satisfied..
                                switch (th.c.value(c->b)) {
                                    case True:
                                        // nothing to propagate..
                                        break;
                                    case False:
                                        // we have a propositional inconsistency..
                                        return new constr(th.c, c_expl);
                                        break;
                                    case Undefined:
                                        // we propagate information to the sat core..
                                        th.record(c_expl);
                                        break;
                                    default:
                                        break;
                                }
                                break;
                            default:
                                break;
                        }
                    }
                }
            }
        }
        return nullptr;
    }

    constr* t_row::propagate_ub(var x) {
        if (l.vars.at(x) > 0) {
            double ub;
            std::vector<lit> expl;
            for (const auto& term : l.vars) {
                if (term.second > 0) {
                    if (th.bounds(term.first).ub < std::numeric_limits<double>::infinity()) {
                        // nothing to propagate..
                        return nullptr;
                    } else {
                        ub += term.second * th.bounds(term.first).ub;
                        expl.push_back(lit(th.s_asrts["x" + std::to_string(term.first) + " <= " + std::to_string(th.assigns[term.first].ub)], false));
                    }
                } else if (term.second < 0) {
                    if (th.bounds(term.first).lb > -std::numeric_limits<double>::infinity()) {
                        // nothing to propagate..
                        return nullptr;
                    } else {
                        ub += term.second * th.bounds(term.first).lb;
                        expl.push_back(lit(th.s_asrts["x" + std::to_string(term.first) + " >= " + std::to_string(th.assigns[term.first].lb)], false));
                    }
                }
            }
            if (ub < th.bounds(x).ub) {
                for (const auto& c : th.a_watches[x]) {
                    if (ub > c->v) {
                        std::vector<lit> c_expl = expl;
                        switch (c->o) {
                            case leq:
                                c_expl.push_back(lit(c->b, false));
                                // the assertion is unsatisfable..
                                switch (th.c.value(c->b)) {
                                    case True:
                                        // we have a propositional inconsistency..
                                        return new constr(th.c, c_expl);
                                        break;
                                    case False:
                                        // nothing to propagate..
                                        break;
                                    case Undefined:
                                        // we propagate information to the sat core..
                                        th.record(c_expl);
                                        break;
                                    default:
                                        break;
                                }
                                break;
                            case geq:
                                c_expl.push_back(lit(c->b, true));
                                // the assertion is satisfied..
                                switch (th.c.value(c->b)) {
                                    case True:
                                        // nothing to propagate..
                                        break;
                                    case False:
                                        // we have a propositional inconsistency..
                                        return new constr(th.c, c_expl);
                                        break;
                                    case Undefined:
                                        // we propagate information to the sat core..
                                        th.record(c_expl);
                                        break;
                                    default:
                                        break;
                                }
                                break;
                            default:
                                break;
                        }
                    }
                }
            }
        } else {
            double lb;
            std::vector<lit> expl;
            for (const auto& term : l.vars) {
                if (term.second > 0) {
                    if (th.bounds(term.first).lb > -std::numeric_limits<double>::infinity()) {
                        // nothing to propagate..
                        return nullptr;
                    } else {
                        lb += term.second * th.bounds(term.first).lb;
                        expl.push_back(lit(th.s_asrts["x" + std::to_string(term.first) + " >= " + std::to_string(th.assigns[term.first].lb)], false));
                    }
                } else if (term.second < 0) {
                    if (th.bounds(term.first).ub < std::numeric_limits<double>::infinity()) {
                        // nothing to propagate..
                        return nullptr;
                    } else {
                        lb += term.second * th.bounds(term.first).ub;
                        expl.push_back(lit(th.s_asrts["x" + std::to_string(term.first) + " <= " + std::to_string(th.assigns[term.first].ub)], false));
                    }
                }
            }
            if (lb > th.bounds(x).lb) {
                for (const auto& c : th.a_watches[x]) {
                    if (lb > c->v) {
                        std::vector<lit> c_expl = expl;
                        switch (c->o) {
                            case leq:
                                c_expl.push_back(lit(c->b, false));
                                // the assertion is unsatisfable..
                                switch (th.c.value(c->b)) {
                                    case True:
                                        // we have a propositional inconsistency..
                                        return new constr(th.c, c_expl);
                                        break;
                                    case False:
                                        // nothing to propagate..
                                        break;
                                    case Undefined:
                                        // we propagate information to the sat core..
                                        th.record(c_expl);
                                        break;
                                    default:
                                        break;
                                }
                                break;
                            case geq:
                                c_expl.push_back(lit(c->b, true));
                                // the assertion is satisfied..
                                switch (th.c.value(c->b)) {
                                    case True:
                                        // nothing to propagate..
                                        break;
                                    case False:
                                        // we have a propositional inconsistency..
                                        return new constr(th.c, c_expl);
                                        break;
                                    case Undefined:
                                        // we propagate information to the sat core..
                                        th.record(c_expl);
                                        break;
                                    default:
                                        break;
                                }
                                break;
                            default:
                                break;
                        }
                    }
                }
            }
        }
        return nullptr;
    }

    std::ostream& operator<<(std::ostream& os, const t_row& obj) {
        os << "x" << std::to_string(obj.x) << " = " << obj.l;
        double val = obj.l.known_term;
        for (const auto& term : obj.l.vars) {
            val += obj.th.value(term.first) * term.second;
        }
        os << " (" << obj.th.value(obj.x) << " = " << std::to_string(val) << ")";
        return os;
    }
}