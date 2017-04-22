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
 * File:   enum_flaw.h
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 *
 * Created on April 14, 2017, 2:28 PM
 */

#ifndef ENUM_FLAW_H
#define ENUM_FLAW_H

#include "flaw.h"
#include "item.h"
#include "resolver.h"

namespace cg {

    class enum_flaw : public flaw {
    public:
        enum_flaw(causal_graph& g, ratio::enum_item& e);
        enum_flaw(const enum_flaw& orig) = delete;
        virtual ~enum_flaw();

    private:
        bool compute_resolvers(std::vector<resolver*>& rs) override;

        class choose_value : public resolver {
        public:
            choose_value(causal_graph& g, enum_flaw& f, smt::set_item& val);
            choose_value(const choose_value& that) = delete;
            virtual ~choose_value();

        private:
            bool apply() override;

        private:
            smt::var v;
            smt::set_item& val;
        };
    private:
        ratio::enum_item& e;
    };
}

#endif /* ENUM_FLAW_H */

