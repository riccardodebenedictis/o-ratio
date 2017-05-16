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
 * File:   reusable_resource.h
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 *
 * Created on May 16, 2017, 9:45 AM
 */

#ifndef REUSABLE_RESOURCE_H
#define REUSABLE_RESOURCE_H

#include "smart_type.h"
#include "constructor.h"
#include "predicate.h"
#include "flaw.h"
#include "resolver.h"

#define REUSABLE_RESOURCE_NAME "ReusableResource"
#define REUSABLE_RESOURCE_CAPACITY "capacity"
#define REUSABLE_RESOURCE_USE_PREDICATE_NAME "Use"
#define REUSABLE_RESOURCE_USE_AMOUNT_NAME "amount"

namespace cg {

    class causal_graph;

    class reusable_resource : public smart_type {
    public:
        reusable_resource(cg::causal_graph& g);
        reusable_resource(const reusable_resource& orig) = delete;
        virtual ~reusable_resource();

    private:
        std::vector<flaw*> get_flaws() override;

        void new_predicate(ratio::predicate& p) override;
        bool new_fact(ratio::atom& a) override;
        bool new_goal(ratio::atom& a) override;

        class reusable_resource_constructor : public ratio::constructor {
        public:

            reusable_resource_constructor(reusable_resource& rr) : ratio::constructor(rr._solver, rr,{new ratio::field(rr.g.get_type("real"), REUSABLE_RESOURCE_CAPACITY)}) { }
            reusable_resource_constructor(reusable_resource_constructor&&) = delete;

            virtual ~reusable_resource_constructor() { }

        private:

            bool invoke(ratio::item& i, const std::vector<ratio::expr>& exprs) override {
                return true;
            }
        };

        class use_predicate : public ratio::predicate {
        public:

            use_predicate(reusable_resource& rr);
            use_predicate(use_predicate&&) = delete;

            virtual ~use_predicate();

        private:
            bool apply_rule(ratio::atom& a) const override;
        };

        class reusable_resource_atom_listener : public atom_listener {
        public:
            reusable_resource_atom_listener(reusable_resource& rr, ratio::atom& a);
            reusable_resource_atom_listener(reusable_resource_atom_listener&&) = delete;
            virtual ~reusable_resource_atom_listener();

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
            reusable_resource& rr;
        };

        class reusable_resource_flaw : public flaw {
        public:
            reusable_resource_flaw(causal_graph& g, const std::set<ratio::atom*>& overlapping_atoms);
            reusable_resource_flaw(reusable_resource_flaw&&) = delete;
            virtual ~reusable_resource_flaw();

            std::string get_label() const override;

        private:
            void compute_resolvers() override;

        private:
            const std::set<ratio::atom*> overlapping_atoms;
        };

        class rr_resolver : public resolver {
        public:
            rr_resolver(causal_graph& g, const smt::lin& cost, reusable_resource_flaw& f, const smt::lit& to_do);
            rr_resolver(const rr_resolver& that) = delete;
            virtual ~rr_resolver();

        private:
            bool apply() override;

        private:
            const smt::lit to_do;
        };

        class order_resolver : public rr_resolver {
        public:
            order_resolver(causal_graph& g, const smt::lin& cost, reusable_resource_flaw& f, const ratio::atom& before, const ratio::atom& after, const smt::lit& to_do);
            order_resolver(const order_resolver& that) = delete;
            virtual ~order_resolver();

            std::string get_label() const override;

        private:
            const ratio::atom& before;
            const ratio::atom& after;
        };

        class displace_resolver : public rr_resolver {
        public:
            displace_resolver(causal_graph& g, const smt::lin& cost, reusable_resource_flaw& f, const ratio::atom& a, const ratio::item& i, const smt::lit& to_do);
            displace_resolver(const displace_resolver& that) = delete;
            virtual ~displace_resolver();

            std::string get_label() const override;

        private:
            const ratio::atom& a;
            const ratio::item& i;
        };

    private:
        std::set<ratio::item*> to_check;
        std::vector<std::pair<ratio::atom*, reusable_resource_atom_listener*>> atoms;
    };
}

#endif /* REUSABLE_RESOURCE_H */

