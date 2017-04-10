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
 * File:   interval.h
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 *
 * Created on April 10, 2017, 5:19 PM
 */

#ifndef INTERVAL_H
#define INTERVAL_H

#include <iostream>

namespace smt {

    class interval {
    public:
        interval();
        interval(double value);
        interval(double lb, double ub);

        bool consistent() const;
        bool constant() const;
        bool intersecting(const interval& i) const;
        bool contains(const interval& i) const;

        bool operator!=(const interval& right) const;
        bool operator<(const interval& right) const;
        bool operator<=(const interval& right) const;
        bool operator==(const interval& right) const;
        bool operator>=(const interval& right) const;
        bool operator>(const interval& right) const;

        interval operator&&(const interval& rhs);

        interval operator+(const interval& rhs);
        interval operator+(const double& rhs);
        friend interval operator+(const double& lhs, const interval& rhs);

        interval operator-(const interval& rhs);
        interval operator-(const double& rhs);
        friend interval operator-(const double& lhs, const interval& rhs);

        interval operator*(const interval& rhs);
        interval operator*(const double& rhs);
        friend interval operator*(const double& lhs, const interval& rhs);

        interval operator/(const interval& rhs);
        interval operator/(const double& rhs);
        friend interval operator/(const double& lhs, const interval& rhs);

        interval operator+=(const interval& right);
        interval operator+=(const double& right);

        interval operator-=(const interval& right);
        interval operator-=(const double& right);

        interval operator*=(const interval& right);
        interval operator*=(const double& right);

        interval operator/=(const interval& right);
        interval operator/=(const double& right);

        interval operator-() const;

        friend std::ostream& operator<<(std::ostream& os, const interval& obj);

    public:
        double lb;
        double ub;
    };
}

#endif /* INTERVAL_H */

