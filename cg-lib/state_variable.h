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
 * File:   state_variable.h
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 *
 * Created on April 21, 2017, 2:08 PM
 */

#ifndef STATE_VARIABLE_H
#define STATE_VARIABLE_H

#include "smart_type.h"
#include "constructor.h"
#include "flaw.h"
#include "resolver.h"

#define STATE_VARIABLE_NAME "StateVariable"

namespace cg {

    class causal_graph;

    class state_variable : public smart_type {
    public:
        state_variable(cg::causal_graph g);
        state_variable(const state_variable& orig) = delete;
        virtual ~state_variable();

    private:
        std::vector<flaw*> get_flaws() override;

        void new_predicate(ratio::predicate& p) override;
        bool new_fact(ratio::atom& a) override;
        bool new_goal(ratio::atom& a) override;

        class state_variable_constructor : public ratio::constructor {
        public:

            state_variable_constructor(state_variable& sv) : ratio::constructor(sv._solver, sv,{}) { }
            state_variable_constructor(state_variable_constructor&&) = delete;

            virtual ~state_variable_constructor() { }

        private:

            bool invoke(ratio::item& i, const std::vector<ratio::expr>& exprs) override {
                return true;
            }
        };

        class state_variable_atom_listener : public atom_listener {
        public:
            state_variable_atom_listener(state_variable& sv, ratio::atom& a);
            state_variable_atom_listener(state_variable_atom_listener&&) = delete;
            virtual ~state_variable_atom_listener();

        private:
            void something_changed();

            void sat_value_change(size_t var) override {
                something_changed();
            }

            void la_value_change(size_t var) override {
                something_changed();
            }

            void set_value_change(size_t var) override {
                something_changed();
            }

        protected:
            state_variable& sv;
        };

        class state_variable_flaw : public flaw {
        public:
            state_variable_flaw(causal_graph& g, const std::set<ratio::atom*>& overlapping_atoms);
            state_variable_flaw(state_variable_flaw&&) = delete;
            virtual ~state_variable_flaw();

        private:
            bool compute_resolvers(std::vector<resolver*>& rs) override;

        private:
            const std::set<ratio::atom*> overlapping_atoms;
        };

        class sv_resolver : public resolver {
        public:
            sv_resolver(causal_graph& g, const smt::lin& cost, state_variable_flaw& f, const smt::lit& to_do);
            sv_resolver(const sv_resolver& that) = delete;
            virtual ~sv_resolver();

        private:
            bool apply() override;

        private:
            const smt::lit to_do;
        };

        class order_resolver : public sv_resolver {
        public:
            order_resolver(causal_graph& g, const smt::lin& cost, state_variable_flaw& f, const ratio::atom& before, const ratio::atom& after, const smt::lit& to_do);
            order_resolver(const order_resolver& that) = delete;
            virtual ~order_resolver();

        private:
            const ratio::atom& before;
            const ratio::atom& after;
        };

        class displace_resolver : public sv_resolver {
        public:
            displace_resolver(causal_graph& g, const smt::lin& cost, state_variable_flaw& f, const ratio::atom& a, const ratio::item& i, const smt::lit& to_do);
            displace_resolver(const displace_resolver& that) = delete;
            virtual ~displace_resolver();

        private:
            const ratio::atom& a;
            const ratio::item& i;
        };

    private:
        std::set<ratio::item*> to_check;
        std::vector<std::pair<ratio::atom*, atom_listener*>> atoms;
    };
}

#endif /* STATE_VARIABLE_H */

