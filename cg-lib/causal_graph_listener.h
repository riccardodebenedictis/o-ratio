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
 * File:   causal_graph_listener.h
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 *
 * Created on April 18, 2017, 6:34 PM
 */

#ifndef CAUSAL_GRAPH_LISTENER_H
#define CAUSAL_GRAPH_LISTENER_H

#include "sat_value_listener.h"

namespace cg {

    class causal_graph;
    class flaw;
    class resolver;

    class causal_graph_listener {
        friend class causal_graph;
        friend class flaw_listener;
        friend class resolver_listener;
    public:
        causal_graph_listener(causal_graph& g);
        causal_graph_listener(const causal_graph_listener& orig) = delete;
        virtual ~causal_graph_listener();

        causal_graph& get_causal_graph() const {
            return g;
        }

        friend std::ostream& operator<<(std::ostream& os, const causal_graph_listener& obj);

    private:
        void new_flaw(const flaw& f);

        virtual void flaw_created(const flaw& f);
        virtual void flaw_state_changed(const flaw& f);
        virtual void flaw_cost_changed(const flaw& f);
        virtual void current_flaw(const flaw& f);

        void new_resolver(const resolver& r);

        virtual void resolver_created(const resolver& r);
        virtual void resolver_state_changed(const resolver& r);
        virtual void current_resolver(const resolver& r);

        virtual void causal_link_added(const flaw& f, const resolver& r) { }

        class flaw_listener : public smt::sat_value_listener {
        public:
            flaw_listener(causal_graph_listener& l, const flaw& f);
            flaw_listener(const flaw_listener& orig) = delete;
            virtual ~flaw_listener();

        private:
            void sat_value_change(smt::var v) override;

        protected:
            causal_graph_listener& l;
            const flaw& f;
        };

        class resolver_listener : public smt::sat_value_listener {
        public:
            resolver_listener(causal_graph_listener& l, const resolver& r);
            resolver_listener(const resolver_listener& orig) = delete;
            virtual ~resolver_listener();

        private:
            void sat_value_change(smt::var v) override;

        protected:
            causal_graph_listener& l;
            const resolver& r;
        };

#ifndef NDEBUG

        inline void delete_file() {
            std::remove("graph.json");
        }

        inline void write_file() {
            std::ofstream state_file;
            state_file.open("graph.json");
            state_file << *this;
            state_file.close();
        }
#endif

    protected:
        causal_graph& g;

    private:
        std::unordered_map<const flaw*, flaw_listener*> flaw_listeners;
        std::unordered_map<const resolver*, resolver_listener*> resolver_listeners;
    };
}

#endif /* CAUSAL_GRAPH_LISTENER_H */

