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
 * File:   item.cpp
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 * 
 * Created on April 12, 2017, 5:09 PM
 */

#include "item.h"
#include "core.h"
#include "type.h"
#include "field.h"
#include <cassert>

namespace ratio {

    item::item(core& c, env& e, const type& t) : env(c, e), t(t) { }

    item::~item() { }

    smt::var item::eq(item& i) noexcept {
        if (this == &i) {
            return smt::TRUE;
        } else if (enum_item * ei = dynamic_cast<enum_item*> (&i)) {
            return ei->eq(*this);
        } else {
            std::vector<smt::lit> eqs;
            std::queue<const type*> q;
            q.push(&t);
            while (!q.empty()) {
                for (const auto& f : q.front()->get_fields()) {
                    if (!f.second->synthetic) {
                        eqs.push_back(smt::lit(get(f.first)->eq(*i.get(f.first)), true));
                    }
                }
                for (const auto& st : q.front()->get_supertypes()) {
                    q.push(st);
                }
                q.pop();
            }

            if (eqs.empty()) {
                return smt::TRUE;
            } else if (eqs.size() == 1) {
                return eqs.begin()->v;
            } else {
                return _core.new_conj(eqs);
            }
        }
    }

    bool item::equates(const item& i) const noexcept {
        if (this == &i) {
            return true;
        } else if (const enum_item * ei = dynamic_cast<const enum_item*> (&i)) {
            return ei->equates(*this);
        } else {
            std::queue<const type*> q;
            q.push(&t);
            while (!q.empty()) {
                for (const auto& f : q.front()->get_fields()) {
                    if (!f.second->synthetic) {
                        if (!get(f.first)->equates(*i.get(f.first))) {
                            return false;
                        }
                    }
                }
                for (const auto& st : q.front()->get_supertypes()) {
                    q.push(st);
                }
                q.pop();
            }
            return true;
        }
    }

    bool_item::bool_item(core& c, const smt::lit& l) : item(c, c, c.get_type(BOOL_KEYWORD)), l(l) { }

    bool_item::~bool_item() { }

    smt::var bool_item::eq(item& i) noexcept {
        if (this == &i) {
            return smt::TRUE;
        } else if (bool_item * be = dynamic_cast<bool_item*> (&i)) {
            return _core.new_eq(l, be->l);
        } else {
            return smt::FALSE;
        }
    }

    bool bool_item::equates(const item& i) const noexcept {
        if (this == &i) {
            return true;
        } else if (const bool_item * be = dynamic_cast<const bool_item*> (&i)) {
            smt::lbool c_val = _core.bool_value(l);
            smt::lbool i_val = _core.bool_value(be->l);
            return c_val == i_val || c_val == smt::Undefined || i_val == smt::Undefined;
        } else {
            return false;
        }
    }

    arith_item::arith_item(core& c, const type& t, const smt::lin& l) : item(c, c, t), l(l) {
        assert(&t == &c.get_type(INT_KEYWORD) || &t == &c.get_type(REAL_KEYWORD));
    }

    arith_item::~arith_item() { }

    smt::var arith_item::eq(item& i) noexcept {
        if (this == &i) {
            return smt::TRUE;
        } else if (arith_item * ae = dynamic_cast<arith_item*> (&i)) {
            return _core.new_eq(l, ae->l);
        } else {
            return smt::FALSE;
        }
    }

    bool arith_item::equates(const item& i) const noexcept {
        if (this == &i) {
            return true;
        } else if (const arith_item * ae = dynamic_cast<const arith_item*> (&i)) {
            smt::interval c_val = _core.arith_bounds(l);
            smt::interval i_val = _core.arith_bounds(ae->l);
            return c_val.intersecting(i_val);
        } else {
            return false;
        }
    }

    string_item::string_item(core& c, const std::string& l) : item(c, c, c.get_type(STRING_KEYWORD)), l(l) { }

    string_item::~string_item() { }

    std::string string_item::get_value() {
        return l;
    }

    smt::var string_item::eq(item& i) noexcept {
        if (this == &i) {
            return smt::TRUE;
        } else if (string_item * se = dynamic_cast<string_item*> (&i)) {
            return l.compare(se->l) == 0 ? smt::TRUE : smt::FALSE;
        } else {
            return smt::FALSE;
        }
    }

    bool string_item::equates(const item& i) const noexcept {
        if (this == &i) {
            return true;
        } else if (const string_item * se = dynamic_cast<const string_item*> (&i)) {
            return l.compare(se->l) == 0;
        } else {
            return false;
        }
    }

    enum_item::enum_item(core& c, const type& t, smt::var ev) : item(c, c, t), ev(ev) { }

    enum_item::~enum_item() { }

    expr enum_item::get(const std::string& name) const {
        if (items.find(name) == items.end()) {
            std::unordered_set<smt::set_item*> vs = _core.enum_value(ev);
            if (vs.size() == 1) {
                return (static_cast<item*> (*vs.begin()))->get(name);
            } else {
                std::vector<item*> c_vals;
                std::vector<item*> f_vals;
                for (const auto& val : vs) {
                    c_vals.push_back(static_cast<item*> (val));
                    f_vals.push_back(& * static_cast<item*> (val)->get(name));
                    if (dynamic_cast<enum_item*> (f_vals.back())) {
                        std::unexpected();
                    }
                }

                std::unordered_set<item*> vals;
                for (unsigned int i = 0; i < c_vals.size(); i++) {
                    vals.insert(f_vals[i]);
                }
                enum_expr e = _core.new_enum(t.get_field(name).t, vals);

                for (unsigned int i = 0; i < c_vals.size(); i++) {
                    bool af = _core.eq(smt::lit(_core.allows(ev, *c_vals[i]), true), smt::lit(_core.allows(e->ev, *f_vals[i]), true));
                    assert(af);
                }

                const_cast<enum_item*> (this)->items.insert({name, e});
            }
        }

        return items.at(name);
    }

    smt::var enum_item::eq(item& i) noexcept {
        if (this == &i) {
            return smt::TRUE;
        } else if (enum_item * ee = dynamic_cast<enum_item*> (&i)) {
            return _core.new_eq(ev, ee->ev);
        } else {
            return _core.allows(ev, i);
        }
    }

    bool enum_item::equates(const item& i) const noexcept {
        if (this == &i) {
            return true;
        } else if (const enum_item * ei = dynamic_cast<const enum_item*> (&i)) {
            std::unordered_set<smt::set_item*> c_vals = _core.enum_value(ev);
            std::unordered_set<smt::set_item*> i_vals = _core.enum_value(ei->ev);
            for (const auto& c_v : c_vals) {
                if (i_vals.find(c_v) != i_vals.end()) {
                    return true;
                }
            }
            return false;
        } else {
            std::unordered_set<smt::set_item*> c_vals = _core.enum_value(ev);
            return c_vals.find(const_cast<smt::set_item*> (static_cast<const smt::set_item*> (&i))) != c_vals.end();
        }
    }
}