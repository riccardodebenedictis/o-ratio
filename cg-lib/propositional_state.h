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
 * File:   propositional_state.h
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 *
 * Created on May 17, 2017, 11:53 AM
 */

#ifndef PROPOSITIONAL_STATE_H
#define PROPOSITIONAL_STATE_H

#include "smart_type.h"
#include "constructor.h"
#include "predicate.h"
#include "flaw.h"
#include "resolver.h"

#define PROPOSITIONAL_STATE_NAME "PropositionalState"
#define POLARITY "polarity"

namespace cg {

    class causal_graph;

    class propositional_state : public smart_type {
    public:
        propositional_state(cg::causal_graph& g);
        propositional_state(const propositional_state& orig) = delete;
        virtual ~propositional_state();

    private:
        std::vector<flaw*> get_flaws() override;

        void new_predicate(ratio::predicate& p) override;
        bool new_fact(ratio::atom& a) override;
        bool new_goal(ratio::atom& a) override;

        class ps_constructor : public ratio::constructor {
        public:

            ps_constructor(propositional_state& ps) : ratio::constructor(ps._solver, ps,{}) { }
            ps_constructor(ps_constructor&&) = delete;

            virtual ~ps_constructor() { }

        private:

            bool invoke(ratio::item& i, const std::vector<ratio::expr>& exprs) override {
                return true;
            }
        };

        class ps_atom_listener : public atom_listener {
        public:
            ps_atom_listener(propositional_state& ps, ratio::atom& a);
            ps_atom_listener(ps_atom_listener&&) = delete;
            virtual ~ps_atom_listener();

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
            propositional_state& ps;
        };

        class ps_flaw : public flaw {
        public:
            ps_flaw(causal_graph& g, const std::set<ratio::atom*>& overlapping_atoms);
            ps_flaw(ps_flaw&&) = delete;
            virtual ~ps_flaw();

            std::string get_label() const override;

        private:
            void compute_resolvers() override;

        private:
            const std::set<ratio::atom*> overlapping_atoms;
        };

        class ps_resolver : public resolver {
        public:
            ps_resolver(causal_graph& g, const smt::lin& cost, ps_flaw& f, const smt::lit& to_do);
            ps_resolver(const ps_resolver& that) = delete;
            virtual ~ps_resolver();

        private:
            bool apply() override;

        private:
            const smt::lit to_do;
        };

        class order_resolver : public ps_resolver {
        public:
            order_resolver(causal_graph& g, const smt::lin& cost, ps_flaw& f, const ratio::atom& before, const ratio::atom& after, const smt::lit& to_do);
            order_resolver(const order_resolver& that) = delete;
            virtual ~order_resolver();

            std::string get_label() const override;

        private:
            const ratio::atom& before;
            const ratio::atom& after;
        };

        class displace_resolver : public ps_resolver {
        public:
            displace_resolver(causal_graph& g, const smt::lin& cost, ps_flaw& f, const ratio::atom& a, const std::string& f_name, const ratio::item& i, const smt::lit& to_do);
            displace_resolver(const displace_resolver& that) = delete;
            virtual ~displace_resolver();

            std::string get_label() const override;

        private:
            const ratio::atom& a;
            const std::string f_name;
            const ratio::item& i;
        };

    private:
        std::set<ratio::atom*> to_check;
        std::vector<std::pair<ratio::atom*, ps_atom_listener*>> atoms;
    };
}

#endif /* PROPOSITIONAL_STATE_H */

