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
 * File:   env_ptr.h
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 *
 * Created on April 12, 2017, 5:22 PM
 */

#ifndef ENV_PTR_H
#define ENV_PTR_H

namespace ratio {

    class env;
    class item;
    class bool_item;
    class arith_item;
    class string_item;
    class enum_item;

    template<typename T>
    class env_ptr;

    typedef env_ptr<env> context;
    typedef env_ptr<item> expr;
    typedef env_ptr<bool_item> bool_expr;
    typedef env_ptr<arith_item> arith_expr;
    typedef env_ptr<string_item> string_expr;
    typedef env_ptr<enum_item> enum_expr;

    template<typename T>
    class env_ptr final {
    public:

        env_ptr(T * const ptr) : ptr(ptr) {
            ptr->ref_count++;
        }

        env_ptr(const env_ptr& that) : ptr(that.ptr) {
            ptr->ref_count++;
        }

        ~env_ptr() {
            ptr->ref_count--;
            if (ptr->ref_count == 0) {
                delete ptr;
            }
        }

        T& operator*() const {
            return *ptr;
        }

        T* operator->() const {
            return ptr;
        }

        operator context() {
            return context(ptr);
        }

        operator expr() {
            return expr(ptr);
        }

        operator bool_expr() {
            return bool_expr(static_cast<bool_item*> (ptr));
        }

        operator arith_expr() {
            return arith_expr(static_cast<arith_item*> (ptr));
        }

        operator string_expr() {
            return string_expr(static_cast<string_item*> (ptr));
        }

        operator enum_expr() {
            return enum_expr(static_cast<enum_item*> (ptr));
        }

        bool operator==(const env_ptr<T>& right) const {
            return ptr == right.ptr;
        }

        bool operator!=(const env_ptr<T>& right) const {
            return !(*this == right);
        }

    private:
        T * const ptr;
    };
}

#endif /* ENV_PTR_H */

