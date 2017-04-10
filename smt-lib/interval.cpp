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
 * File:   interval.cpp
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 * 
 * Created on April 10, 2017, 5:19 PM
 */

#include "interval.h"
#include <limits>

namespace smt {

    interval::interval() : lb(-std::numeric_limits<double>::infinity()), ub(std::numeric_limits<double>::infinity()) { }

    interval::interval(double value) : lb(value), ub(value) { }

    interval::interval(double lb, double ub) : lb(lb), ub(ub) { }

    bool interval::consistent() const {
        return lb <= ub;
    }

    bool interval::constant() const {
        return lb == ub;
    }

    bool interval::intersecting(const interval& i) const {
        return ub >= i.lb && lb <= i.ub;
    }

    bool interval::contains(const interval& i) const {
        return lb <= i.lb && ub >= i.ub;
    }

    bool interval::operator!=(const interval& right) const {
        return ub < right.lb || lb > right.ub;
    }

    bool interval::operator<(const interval& right) const {
        return ub < right.lb;
    }

    bool interval::operator<=(const interval& right) const {
        return ub <= right.lb;
    }

    bool interval::operator==(const interval& right) const {
        return constant() && right.constant() && lb == right.lb;
    }

    bool interval::operator>=(const interval& right) const {
        return lb >= right.ub;
    }

    bool interval::operator>(const interval& right) const {
        return lb > right.ub;
    }

    interval interval::operator&&(const interval& rhs) {
        return interval(std::max(lb, rhs.lb), std::min(ub, rhs.ub));
    }

    interval interval::operator+(const interval& rhs) {
        return interval(lb + rhs.lb, ub + rhs.ub);
    }

    interval interval::operator+(const double& rhs) {
        return interval(lb + rhs, ub + rhs);
    }

    interval operator+(const double& lhs, const interval& rhs) {
        return interval(lhs + rhs.lb, lhs + rhs.ub);
    }

    interval interval::operator-(const interval& rhs) {
        return interval(lb - rhs.ub, ub - rhs.lb);
    }

    interval interval::operator-(const double& rhs) {
        return interval(lb - rhs, ub - rhs);
    }

    interval operator-(const double& lhs, const interval& rhs) {
        return interval(lhs - rhs.ub, lhs - rhs.lb);
    }

    interval interval::operator*(const interval& rhs) {
        interval result(std::numeric_limits<double>::infinity(), -std::numeric_limits<double>::infinity());
        for (const auto& i :{lb * rhs.lb, lb * rhs.ub, ub * rhs.lb, ub * rhs.ub}) {
            if (i < result.lb)
                result.lb = i;
            if (i > result.ub)
                result.ub = i;
        }
        return result;
    }

    interval interval::operator*(const double& rhs) {
        if (rhs >= 0) {
            return interval(lb * rhs, ub * rhs);
        } else {
            return interval(ub * rhs, lb * rhs);
        }
    }

    interval operator*(const double& lhs, const interval& rhs) {
        if (lhs >= 0) {
            return interval(rhs.lb * lhs, rhs.ub * lhs);
        } else {
            return interval(rhs.ub * lhs, rhs.lb * lhs);
        }
    }

    interval interval::operator/(const interval& rhs) {
        if (rhs.lb <= 0 && rhs.ub >= 0) {
            // 0 appears in the denominator..
            return interval();
        } else {
            interval result(std::numeric_limits<double>::infinity(), -std::numeric_limits<double>::infinity());
            for (const auto& i :{lb / rhs.lb, lb / rhs.ub, ub / rhs.lb, ub / rhs.ub}) {
                if (i < result.lb)
                    result.lb = i;
                if (i > result.ub)
                    result.ub = i;
            }
            return result;
        }
    }

    interval interval::operator/(const double& rhs) {
        if (rhs >= 0) {
            return interval(lb / rhs, ub / rhs);
        } else {
            return interval(ub / rhs, lb / rhs);
        }
    }

    interval operator/(const double& lhs, const interval& rhs) {
        if (rhs.lb <= 0 && rhs.ub >= 0) {
            // 0 appears in the denominator..
            return interval();
        } else {
            interval result(std::numeric_limits<double>::infinity(), -std::numeric_limits<double>::infinity());
            for (const auto& i :{lhs / rhs.lb, lhs / rhs.ub}) {
                if (i < result.lb)
                    result.lb = i;
                if (i > result.ub)
                    result.ub = i;
            }
            return result;
        }
    }

    interval interval::operator+=(const interval& right) {
        lb += right.lb;
        ub += right.ub;
        return *this;
    }

    interval interval::operator+=(const double& right) {
        lb += right;
        ub += right;
        return *this;
    }

    interval interval::operator-=(const interval& right) {
        lb -= right.ub;
        ub -= right.lb;
        return *this;
    }

    interval interval::operator-=(const double& right) {
        lb -= right;
        ub -= right;
        return *this;
    }

    interval interval::operator*=(const interval& right) {
        double c_lb = std::numeric_limits<double>::infinity();
        double c_ub = -std::numeric_limits<double>::infinity();
        for (const auto& i :{lb * right.lb, lb * right.ub, ub * right.lb, ub * right.ub}) {
            if (i < c_lb)
                c_lb = i;
            if (i > c_ub)
                c_ub = i;
        }
        lb = c_lb;
        ub = c_ub;
        return *this;
    }

    interval interval::operator*=(const double& right) {
        if (right >= 0) {
            lb *= right;
            ub *= right;
        } else {
            double c_lb = lb;
            lb = ub * right;
            ub = c_lb * right;
        }
        return *this;
    }

    interval interval::operator/=(const interval& right) {
        if (right.lb <= 0 && right.ub >= 0) {
            // 0 appears in the denominator..
            lb = -std::numeric_limits<double>::infinity();
            ub = std::numeric_limits<double>::infinity();
        } else {
            double c_lb = std::numeric_limits<double>::infinity();
            double c_ub = -std::numeric_limits<double>::infinity();
            for (const auto& i :{lb / right.lb, lb / right.ub, ub / right.lb, ub / right.ub}) {
                if (i < c_lb)
                    c_lb = i;
                if (i > c_ub)
                    c_ub = i;
            }
            lb = c_lb;
            ub = c_ub;
        }
        return *this;
    }

    interval interval::operator/=(const double& right) {
        if (right >= 0) {
            lb /= right;
            ub /= right;
        } else {
            double c_lb = lb;
            lb = ub / right;
            ub = c_lb / right;
        }
        return *this;
    }

    interval interval::operator-() const {
        return std::move(interval(-ub, -lb));
    }

    std::ostream& operator<<(std::ostream& os, const interval& obj) {
        os << "[" << std::to_string(obj.lb) << ", " << std::to_string(obj.ub) << "]";
        return os;
    }
}