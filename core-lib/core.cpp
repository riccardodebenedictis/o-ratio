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
 * File:   core.cpp
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 * 
 * Created on April 12, 2017, 4:28 PM
 */

#include "core.h"
#include "field.h"
#include "predicate.h"
#include "method.h"
#include "atom.h"
#include "type_declaration_listener.h"
#include "type_refinement_listener.h"
#include "statement_visitor.h"

namespace ratio {

    core::core(solver& slv) : scope(slv, *this), env(slv, this), sat(), la(sat), set(sat) {
        types.insert({BOOL_KEYWORD, new bool_type(slv)});
        types.insert({INT_KEYWORD, new int_type(slv)});
        types.insert({REAL_KEYWORD, new real_type(slv)});
        types.insert({STRING_KEYWORD, new string_type(slv)});
    }

    core::~core() {
        for (const auto& p : parsers) {
            delete p;
        }
        for (const auto& p : predicates) {
            delete p.second;
        }
        for (const auto& t : types) {
            delete t.second;
        }
        for (const auto& ms : methods) {
            for (const auto& m : ms.second) {
                delete m;
            }
        }
    }

    bool core::read(const std::string& script) {
        p = new ratioParser(new antlr4::CommonTokenStream(new ratioLexer(new antlr4::ANTLRInputStream(script))));
        parsers.push_back(p);
        ratioParser::Compilation_unitContext* cu = p->compilation_unit();
        type_declaration_listener td(scope::_solver);
        type_refinement_listener tr(scope::_solver);
        antlr4::tree::ParseTreeWalker::DEFAULT.walk(&td, cu);
        antlr4::tree::ParseTreeWalker::DEFAULT.walk(&tr, cu);
        context ctx(this);
        if (!statement_visitor(scope::_solver, ctx).visit(cu).as<bool>()) {
            return false;
        }
        p = nullptr;
        if (!sat.check()) {
            return false;
        } else {
#ifndef NDEBUG
            write_file();
#endif
            return true;
        }
    }

    bool core::read(const std::vector<std::string>& files) {
        std::vector<snippet*> snippets;
        for (const auto& f : files) {
            p = new ratioParser(new antlr4::CommonTokenStream(new ratioLexer(new antlr4::ANTLRFileStream(f))));
            parsers.push_back(p);
            snippet* s = new snippet(f, *p, p->compilation_unit());
            snippets.push_back(s);
        }
        type_declaration_listener td(scope::_solver);
        for (const auto& s : snippets) {
            antlr4::tree::ParseTreeWalker::DEFAULT.walk(&td, s->cu);
        }
        type_refinement_listener tr(scope::_solver);
        for (const auto& s : snippets) {
            antlr4::tree::ParseTreeWalker::DEFAULT.walk(&tr, s->cu);
        }
        context ctx(this);
        statement_visitor sv(scope::_solver, ctx);
        for (const auto& s : snippets) {
            p = &s->p;
            if (!sv.visit(s->cu).as<bool>()) {
                return false;
            }
        }
        p = nullptr;
        if (!sat.check()) {
            return false;
        } else {
#ifndef NDEBUG
            write_file();
#endif
            return true;
        }
    }

    bool_expr core::new_bool() {
        return new bool_item(scope::_solver, smt::lit(sat.new_var(), true));
    }

    bool_expr core::new_bool(const bool& val) {
        return new bool_item(scope::_solver, smt::lit(val, true));
    }

    arith_expr core::new_int() {
        throw std::runtime_error("not supported yet..");
    }

    arith_expr core::new_int(const long& val) {
        throw std::runtime_error("not supported yet..");
    }

    arith_expr core::new_real() {
        return new arith_item(scope::_solver, *types.at(REAL_KEYWORD), smt::lin(la.new_var(), 1));
    }

    arith_expr core::new_real(const double& val) {
        return new arith_item(scope::_solver, *types.at(REAL_KEYWORD), smt::lin(val));
    }

    string_expr core::new_string() {
        return new string_item(scope::_solver, "");
    }

    string_expr core::new_string(const std::string& val) {
        return new string_item(scope::_solver, val);
    }

    expr core::new_enum(const type& t, const std::unordered_set<item*>& allowed_vals) {
        std::unordered_set<smt::set_item*> vals(allowed_vals.begin(), allowed_vals.end());
        if (t.name.compare(BOOL_KEYWORD) == 0) {
            bool_expr b = new_bool();
            std::vector<smt::lit> eqs;
            for (const auto& v : allowed_vals) {
                eqs.push_back(smt::lit(sat.new_eq(b->l, dynamic_cast<bool_item*> (v)->l), true));
            }
            bool nc = sat.new_clause(eqs);
            assert(nc);
            return b;
        } else if (t.name.compare(INT_KEYWORD) == 0) {
            arith_expr i = new_int();
            std::vector<smt::lit> eqs;
            for (const auto& v : allowed_vals) {
                smt::var leq_v = la.leq(i->l, dynamic_cast<arith_item*> (v)->l);
                smt::var geq_v = la.geq(i->l, dynamic_cast<arith_item*> (v)->l);
                smt::var eq_v = sat.new_conj({smt::lit(leq_v, true), smt::lit(geq_v, true)});
                eqs.push_back(smt::lit(eq_v, true));
            }
            bool nc = sat.new_clause(eqs);
            assert(nc);
            return i;
        } else if (t.name.compare(REAL_KEYWORD) == 0) {
            arith_expr r = new_real();
            std::vector<smt::lit> eqs;
            for (const auto& v : allowed_vals) {
                smt::var leq_v = la.leq(r->l, dynamic_cast<arith_item*> (v)->l);
                smt::var geq_v = la.geq(r->l, dynamic_cast<arith_item*> (v)->l);
                smt::var eq_v = sat.new_conj({smt::lit(leq_v, true), smt::lit(geq_v, true)});
                eqs.push_back(smt::lit(eq_v, true));
            }
            bool nc = sat.new_clause(eqs);
            assert(nc);
            return r;
        } else {
            return new enum_item(scope::_solver, t, set.new_var(vals));
        }
    }

    bool_expr core::negate(bool_expr var) {
        return new bool_item(scope::_solver, !var->l);
    }

    bool_expr core::eq(bool_expr left, bool_expr right) {
        return new bool_item(scope::_solver, smt::lit(sat.new_eq(left->l, right->l), true));
    }

    bool_expr core::conj(const std::vector<bool_expr>& exprs) {
        std::vector<smt::lit> lits;
        for (const auto& bex : exprs) {
            lits.push_back(bex->l);
        }
        return new bool_item(scope::_solver, smt::lit(sat.new_conj(lits), true));
    }

    bool_expr core::disj(const std::vector<bool_expr>& exprs) {
        std::vector<smt::lit> lits;
        for (const auto& bex : exprs) {
            lits.push_back(bex->l);
        }
        return new bool_item(scope::_solver, smt::lit(sat.new_disj(lits), true));
    }

    bool_expr core::exct_one(const std::vector<bool_expr>& exprs) {
        std::vector<smt::lit> lits;
        for (const auto& bex : exprs) {
            lits.push_back(bex->l);
        }
        return new bool_item(scope::_solver, smt::lit(sat.new_exct_one(lits), true));
    }

    arith_expr core::add(const std::vector<arith_expr>& exprs) {
        smt::lin l;
        for (const auto& aex : exprs) {
            l += aex->l;
        }
        return new arith_item(scope::_solver, *types.at(REAL_KEYWORD), l);
    }

    arith_expr core::sub(const std::vector<arith_expr>& exprs) {
        smt::lin l;
        for (std::vector<arith_expr>::const_iterator it = exprs.begin(); it != exprs.end(); ++it) {
            if (it == exprs.begin()) {
                l += (*it)->l;
            } else {
                l -= (*it)->l;
            }
        }
        return new arith_item(scope::_solver, *types.at(REAL_KEYWORD), l);
    }

    arith_expr core::mult(const std::vector<arith_expr>& exprs) {
        arith_expr ae = *std::find_if(exprs.begin(), exprs.end(), [&](arith_expr ae) {
            return la.bounds(ae->l).constant(); });
        smt::lin l = ae->l;
        for (const auto& aex : exprs) {
            if (aex != ae) {
                assert(la.bounds(aex->l).constant() && "non-linear expression..");
                l *= la.value(aex->l);
            }
        }
        return new arith_item(scope::_solver, *types.at(REAL_KEYWORD), l);
    }

    arith_expr core::div(arith_expr left, arith_expr right) {
        assert(la.bounds(right->l).constant() && "non-linear expression..");
        return new arith_item(scope::_solver, *types.at(REAL_KEYWORD), left->l / la.value(right->l));
    }

    arith_expr core::minus(arith_expr ex) {
        return new arith_item(scope::_solver, *types.at(REAL_KEYWORD), -ex->l);
    }

    bool_expr core::lt(arith_expr left, arith_expr right) {
        throw std::runtime_error("not supported yet..");
    }

    bool_expr core::leq(arith_expr left, arith_expr right) {
        return new bool_item(scope::_solver, smt::lit(la.leq(left->l, right->l), true));
    }

    bool_expr core::eq(arith_expr left, arith_expr right) {
        return new bool_item(scope::_solver, smt::lit(sat.new_conj({smt::lit(la.leq(left->l, right->l), true), smt::lit(la.geq(left->l, right->l), true)}), true));
    }

    bool_expr core::geq(arith_expr left, arith_expr right) {
        return new bool_item(scope::_solver, smt::lit(la.geq(left->l, right->l), true));
    }

    bool_expr core::gt(arith_expr left, arith_expr right) {
        throw std::runtime_error("not supported yet..");
    }

    bool_expr core::eq(expr left, expr right) {
        return new bool_item(scope::_solver, smt::lit(left->eq(*right), true));
    }

    bool core::assert_facts(const std::vector<smt::lit>& facts) {
        for (const auto& f : facts) {
            if (!sat.new_clause({smt::lit(ctr_var, false), f})) {
                return false;
            }
        }
        return true;
    }

    field& core::get_field(const std::string& name) const {
        if (fields.find(name) != fields.end()) {
            return *fields.at(name);
        }

        // not found
        throw std::out_of_range(name);
    }

    method& core::get_method(const std::string& name, const std::vector<const type*>& ts) const {
        if (methods.find(name) != methods.end()) {
            bool found = false;
            for (const auto& mthd : methods.at(name)) {
                if (mthd->args.size() == ts.size()) {
                    found = true;
                    for (size_t i = 0; i < ts.size(); i++) {
                        if (!mthd->args[i]->t.is_assignable_from(*ts[i])) {
                            found = false;
                            break;
                        }
                    }
                    if (found) {
                        return *mthd;
                    }
                }
            }
        }

        // not found
        throw std::out_of_range(name);
    }

    std::vector<method*> core::get_methods() const noexcept {
        std::vector<method*> c_methods;
        for (const auto& ms : methods) {
            c_methods.insert(c_methods.begin(), ms.second.begin(), ms.second.end());
        }
        return c_methods;
    }

    predicate& core::get_predicate(const std::string& name) const {
        if (predicates.find(name) != predicates.end()) {
            return *predicates.at(name);
        }

        // not found
        throw std::out_of_range(name);
    }

    std::unordered_map<std::string, predicate*> core::get_predicates() const noexcept {
        return predicates;
    }

    type& core::get_type(const std::string& name) const {
        if (types.find(name) != types.end()) {
            return *types.at(name);
        }

        // not found
        throw std::out_of_range(name);
    }

    std::unordered_map<std::string, type*> core::get_types() const noexcept {
        return types;
    }

    expr core::get(const std::string& name) const {
        if (items.find(name) != items.end()) {
            return items.at(name);
        }

        throw std::out_of_range(name);
    }

    smt::lbool core::bool_value(const bool_expr& var) const noexcept {
        return sat.value(var->l);
    }

    smt::interval core::arith_bounds(const arith_expr& var) const noexcept {
        return la.bounds(var->l);
    }

    double core::arith_value(const arith_expr& var) const noexcept {
        return la.value(var->l);
    }

    std::unordered_set<smt::set_item*> core::enum_value(const enum_expr& var) const noexcept {
        return set.value(var->ev);
    }

    void core::set_var(smt::var ctr_var) {
        tmp_var = scope::_solver.ctr_var;
        scope::_solver.ctr_var = ctr_var;
    }

    void core::restore_var() {
        scope::_solver.ctr_var = tmp_var;
    }

    std::stringstream to_string(std::unordered_map<std::string, expr> items) {
        std::stringstream ss;
        for (std::unordered_map<std::string, expr>::iterator is_it = items.begin(); is_it != items.end(); ++is_it) {
            if (is_it != items.begin()) {
                ss << ", ";
            }
            ss << "{ \"name\" : \"" << is_it->first << "\", \"type\" : \"" << is_it->second->t.name << "\", \"value\" : ";
            if (bool_item * bi = dynamic_cast<bool_item*> (&*is_it->second)) {
                ss << "{ \"lit\" : \"" << (bi->l.sign ? "b" : "!b") << std::to_string(bi->l.v) << "\", \"val\" : ";
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
            } else if (arith_item * ai = dynamic_cast<arith_item*> (&*is_it->second)) {
                smt::interval bnds = ai->get_solver().la.bounds(ai->l);
                ss << "{ \"lin\" : \"" << ai->l.to_string() << "\", \"val\" : " << std::to_string(ai->get_solver().la.value(ai->l));
                if (bnds.lb > -std::numeric_limits<double>::infinity()) {
                    ss << ", \"lb\" : " << std::to_string(bnds.lb);
                }
                if (bnds.ub < std::numeric_limits<double>::infinity()) {
                    ss << ", \"ub\" : " << std::to_string(bnds.ub);
                }
                ss << " }";
            } else if (enum_item * ei = dynamic_cast<enum_item*> (&*is_it->second)) {
                ss << "{ \"var\" : \"e" << std::to_string(ei->ev) << "\", \"vals\" : [ ";
                std::unordered_set<smt::set_item*> vals = ei->get_solver().set.value(ei->ev);
                for (std::unordered_set<smt::set_item*>::iterator vals_it = vals.begin(); vals_it != vals.end(); ++vals_it) {
                    if (vals_it != vals.begin()) {
                        ss << ", ";
                    }
                    ss << "\"" << std::to_string(reinterpret_cast<uintptr_t> (static_cast<item*> (*vals_it))) << "\"";
                }
                ss << " ] }";
            } else {
                ss << "\"" << std::to_string(reinterpret_cast<uintptr_t> (&*is_it->second)) << "\"";
            }
            ss << " }";
        }
        return ss;
    }

    std::stringstream to_string(item* i) {
        std::stringstream ss;
        ss << "{ \"id\" : \"" << std::to_string(reinterpret_cast<uintptr_t> (i)) << "\", \"type\" : \"" << i->t.name << "\"";
        std::unordered_map<std::string, expr> is = i->get_items();
        if (!is.empty()) {
            ss << ", \"items\" : [ " << to_string(is).str() << " ]";
        }
        ss << "}";
        return ss;
    }

    std::stringstream to_string(atom* a) {
        std::stringstream ss;
        ss << "{ \"id\" : \"" << std::to_string(reinterpret_cast<uintptr_t> (a)) << "\", \"predicate\" : \"" << a->t.name << "\", \"state\" : [";
        std::unordered_set<smt::set_item*> state_vals = a->get_solver().set.value(a->state);
        for (std::unordered_set<smt::set_item*>::iterator vals_it = state_vals.begin(); vals_it != state_vals.end(); ++vals_it) {
            if (vals_it != state_vals.begin()) {
                ss << ", ";
            }
            if (*vals_it == atom::active) {
                ss << "\"Active\"";
            } else if (*vals_it == atom::inactive) {
                ss << "\"Inactive\"";
            } else if (*vals_it == atom::unified) {
                ss << "\"Unified\"";
            }
        }
        ss << "]";
        std::unordered_map<std::string, expr> is = a->get_items();
        if (!is.empty()) {
            ss << ", \"pars\" : [ " << to_string(is).str() << " ]";
        }
        ss << "}";
        return ss;
    }

    std::ostream& operator<<(std::ostream& os, const core& obj) {
        std::set<item*> all_items;
        std::set<atom*> all_atoms;
        for (const auto& p : obj.get_predicates()) {
            for (const auto& a : p.second->get_instances()) {
                all_atoms.insert(static_cast<atom*> (&*a));
            }
        }
        std::queue<type*> q;
        for (const auto& t : obj.get_types()) {
            if (!t.second->primitive) {
                q.push(t.second);
            }
        }
        while (!q.empty()) {
            for (const auto& i : q.front()->get_instances()) {
                all_items.insert(&*i);
            }
            for (const auto& p : q.front()->get_predicates()) {
                for (const auto& a : p.second->get_instances()) {
                    all_atoms.insert(static_cast<atom*> (&*a));
                }
            }
            q.pop();
        }

        os << "{ ";
        if (!all_items.empty()) {
            os << "\"items\" : [";
            for (std::set<item*>::iterator is_it = all_items.begin(); is_it != all_items.end(); ++is_it) {
                if (is_it != all_items.begin()) {
                    os << ", ";
                }
                std::stringstream a = to_string(*is_it);
                os << a.str();
            }
            os << "]";
        }
        if (!all_atoms.empty()) {
            if (!all_items.empty()) {
                os << ", ";
            }
            os << "\"atoms\" : [";
            for (std::set<atom*>::iterator as_it = all_atoms.begin(); as_it != all_atoms.end(); ++as_it) {
                if (as_it != all_atoms.begin()) {
                    os << ", ";
                }
                std::stringstream a = to_string(*as_it);
                os << a.str();
            }
            os << "]";
        }
        if (!all_items.empty() || !all_atoms.empty()) {
            os << ", ";
        }
        std::stringstream rs = to_string(obj.get_items());
        os << "\"refs\" : [" << rs.str() << "] }";
        // Write obj to stream
        return os;
    }
}