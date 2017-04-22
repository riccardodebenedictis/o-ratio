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
 * File:   atom_flaw.h
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 *
 * Created on April 14, 2017, 2:28 PM
 */

#ifndef ATOM_FLAW_H
#define ATOM_FLAW_H

#include "flaw.h"
#include "atom.h"
#include "resolver.h"

namespace cg {

    class atom_flaw : public flaw {
    public:
        atom_flaw(causal_graph& g, ratio::atom& a, bool is_fact);
        atom_flaw(const atom_flaw& orig) = delete;
        virtual ~atom_flaw();

    private:
        bool compute_resolvers(std::vector<resolver*>& rs) override;

        class add_fact : public resolver {
        public:
            add_fact(causal_graph& g, atom_flaw& f, ratio::atom& a);
            add_fact(const add_fact& that) = delete;
            virtual ~add_fact();

        private:
            bool apply() override;

        private:
            ratio::atom& a;
        };

        class expand_goal : public resolver {
        public:
            expand_goal(causal_graph& g, atom_flaw& f, ratio::atom& a);
            expand_goal(const expand_goal& that) = delete;
            virtual ~expand_goal();

        private:
            bool apply() override;

        private:
            ratio::atom& a;
        };

        class unify_atom : public resolver {
        public:
            unify_atom(causal_graph& g, atom_flaw& f, ratio::atom& a, ratio::atom& with, const std::vector<smt::lit>& unif_vars);
            unify_atom(const unify_atom& that) = delete;
            virtual ~unify_atom();

        private:
            bool apply() override;

        private:
            ratio::atom& a;
            ratio::atom& with;
            std::vector<smt::lit> unif_lits;
        };
    private:
        ratio::atom& a;
        bool is_fact;
    };
}

#endif /* ATOM_FLAW_H */

