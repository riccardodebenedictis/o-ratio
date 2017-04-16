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
 * File:   disjunction_flaw.h
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 *
 * Created on April 14, 2017, 2:28 PM
 */

#ifndef DISJUNCTION_FLAW_H
#define DISJUNCTION_FLAW_H

#include "flaw.h"
#include "disjunction.h"
#include "resolver.h"

namespace cg {

    class disjunction_flaw : public flaw {
    public:
        disjunction_flaw(causal_graph& cg, ratio::context& e, ratio::disjunction& d);
        disjunction_flaw(const disjunction_flaw& orig) = delete;
        virtual ~disjunction_flaw();

    private:
        bool compute_resolvers(std::vector<resolver*>& rs) override;

        class choose_conjunction : public resolver {
        public:
            choose_conjunction(causal_graph& cg, disjunction_flaw& f, ratio::context& e, ratio::conjunction& c);
            choose_conjunction(const choose_conjunction& that) = delete;
            virtual ~choose_conjunction();

        private:
            bool apply() override;

        private:
            ratio::context e;
            ratio::conjunction& conj;
        };

    private:
        ratio::context e;
        ratio::disjunction& disj;
    };
}

#endif /* DISJUNCTION_FLAW_H */

