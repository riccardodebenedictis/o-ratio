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
 * File:   env.h
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 *
 * Created on April 12, 2017, 4:38 PM
 */

#ifndef ENV_H
#define ENV_H

#include "env_ptr.h"
#include <unordered_map>
#include <string>

namespace ratio {

    class core;

    class env {
        template<typename T>
        friend class env_ptr;
    public:
        env(core& c, env& e);
        env(const env& orig) = delete;
        virtual ~env();

        core& get_core() const {
            return _core;
        }

        env& get_env() const {
            return _env;
        }

        virtual expr get(const std::string& name) const;
        std::unordered_map<std::string, expr> get_items() const noexcept;

    private:
        unsigned ref_count;

    protected:
        core& _core;
        env& _env;
        std::unordered_map<std::string, expr> items;
    };
}

#endif /* ENV_H */

