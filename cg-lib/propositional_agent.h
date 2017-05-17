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
 * File:   propositional_agent.h
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 *
 * Created on May 17, 2017, 12:29 PM
 */

#ifndef PROPOSITIONAL_AGENT_H
#define PROPOSITIONAL_AGENT_H

#include "smart_type.h"
#include "constructor.h"
#include "flaw.h"
#include "resolver.h"

#define PROPOSITIONAL_AGENT_NAME "PropositionalAgent"

namespace cg {

    class causal_graph;

    class propositional_agent : public smart_type {
    public:
        propositional_agent(cg::causal_graph& g);
        propositional_agent(const propositional_agent& orig) = delete;
        virtual ~propositional_agent();

    private:
        std::vector<flaw*> get_flaws() override;

        bool new_fact(ratio::atom& a) override;
        bool new_goal(ratio::atom& a) override;

        class agnt_constructor : public ratio::constructor {
        public:

            agnt_constructor(propositional_agent& agnt) : ratio::constructor(agnt._solver, agnt,{}) { }
            agnt_constructor(agnt_constructor&&) = delete;

            virtual ~agnt_constructor() { }

        private:

            bool invoke(ratio::item& i, const std::vector<ratio::expr>& exprs) override {
                return true;
            }
        };

        class agnt_atom_listener : public atom_listener {
        public:
            agnt_atom_listener(propositional_agent& agnt, ratio::atom& a);
            agnt_atom_listener(agnt_atom_listener&&) = delete;
            virtual ~agnt_atom_listener();

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
            propositional_agent& agnt;
        };

        class agnt_flaw : public flaw {
        public:
            agnt_flaw(causal_graph& g, const std::set<ratio::atom*>& overlapping_atoms);
            agnt_flaw(agnt_flaw&&) = delete;
            virtual ~agnt_flaw();

            std::string get_label() const override;

        private:
            void compute_resolvers() override;

        private:
            const std::set<ratio::atom*> overlapping_atoms;
        };

        class agnt_resolver : public resolver {
        public:
            agnt_resolver(causal_graph& g, const smt::lin& cost, agnt_flaw& f, const ratio::atom& before, const ratio::atom& after, const smt::lit& to_do);
            agnt_resolver(const agnt_resolver& that) = delete;
            virtual ~agnt_resolver();

            std::string get_label() const override;

        private:
            bool apply() override;

        private:
            const ratio::atom& before;
            const ratio::atom& after;
            const smt::lit to_do;
        };

    private:
        std::set<ratio::atom*> to_check;
        std::vector<std::pair<ratio::atom*, agnt_atom_listener*>> atoms;
    };
}

#endif /* PROPOSITIONAL_AGENT_H */

