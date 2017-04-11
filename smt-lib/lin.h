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
 * File:   lin.h
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 *
 * Created on April 10, 2017, 5:19 PM
 */

#ifndef LIN_H
#define LIN_H

#include <iostream>
#include <map>

namespace smt {

    typedef size_t var;

    class lin {
    public:

        lin();
        lin(double known_term);
        lin(var v, double c);

    public:
        lin operator+(const lin& right) const;
        lin operator+(const double& right) const;
        friend lin operator+(const double& lhs, const lin& rhs);

        lin operator-(const lin& right) const;
        lin operator-(const double& right) const;
        friend lin operator-(const double& lhs, const lin& rhs);

        lin operator*(const double& right) const;
        friend lin operator*(const double& lhs, const lin& rhs);

        lin operator/(const double& right) const;

        lin operator+=(const lin& right);
        lin operator+=(const std::pair<var, double>& term);
        lin operator+=(const double& right);

        lin operator-=(const lin& right);
        lin operator-=(const std::pair<var, double>& term);
        lin operator-=(const double& right);

        lin operator*=(const double& right);

        lin operator/=(const double& right);

        lin operator-() const;

        std::string to_string() const;
        friend std::ostream& operator<<(std::ostream& os, const lin& obj);

    public:
        std::map<var, double> vars;
        double known_term;
    };
}

#endif /* LIN_H */

