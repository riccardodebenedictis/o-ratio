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
 * File:   item.h
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 *
 * Created on April 12, 2017, 5:09 PM
 */

#ifndef ITEM_H
#define ITEM_H

#include "env.h"
#include "sat_core.h"
#include "la_theory.h"
#include "set_theory.h"

namespace ratio {

    class type;

    class item : public env, public smt::set_item {
        friend class scope;
    public:
        item(solver& slv, const context& ctx, const type& t);
        item(const item& orig) = delete;
        virtual ~item();

        virtual smt::var eq(item& i) noexcept;
        virtual bool equates(const item& i) const noexcept;

    public:
        const type& t;
    };

    class bool_item : public item {
    public:
        bool_item(solver& slv, const smt::lit& l);
        bool_item(const bool_item& that) = delete;
        virtual ~bool_item();

        smt::var eq(item& i) noexcept override;
        bool equates(const item& i) const noexcept override;

        friend std::ostream& operator<<(std::ostream& os, const bool_item& obj);

    public:
        smt::lit l;
    };

    class arith_item : public item {
    public:
        arith_item(solver& slv, const type& t, const smt::lin& l);
        arith_item(const arith_item& that) = delete;
        virtual ~arith_item();

        smt::var eq(item& i) noexcept override;
        bool equates(const item& i) const noexcept override;

        friend std::ostream& operator<<(std::ostream& os, const arith_item& obj);

    public:
        const smt::lin l;
    };

    class string_item : public item {
    public:
        string_item(solver& slv, const std::string& l);
        string_item(const string_item& that) = delete;
        virtual ~string_item();

        std::string get_value();

        smt::var eq(item& i) noexcept override;
        bool equates(const item& i) const noexcept override;

        friend std::ostream& operator<<(std::ostream& os, const string_item& obj);

    private:
        std::string l;
    };

    class enum_item : public item {
    public:
        enum_item(solver& slv, const type& t, smt::var ev);
        enum_item(const enum_item& that) = delete;
        virtual ~enum_item();

        expr get(const std::string& name) const override;

        smt::var eq(item& i) noexcept override;
        bool equates(const item& i) const noexcept override;

        friend std::ostream& operator<<(std::ostream& os, const enum_item& obj);

    public:
        const smt::var ev;
    };
}

#endif /* ITEM_H */

