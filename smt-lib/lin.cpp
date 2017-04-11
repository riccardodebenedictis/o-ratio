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
 * File:   lin.cpp
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 * 
 * Created on April 10, 2017, 5:19 PM
 */

#include "lin.h"

namespace smt {

    lin::lin() : known_term(0) { }

    lin::lin(double known_term) : known_term(known_term) { }

    lin::lin(var v, double c) : known_term(0) {
        vars.insert({v, c});
    }

    lin lin::operator+(const lin& right) const {
        lin res = *this;
        for (auto& term : right.vars) {
            if (res.vars.find(term.first) == res.vars.end()) {
                res.vars.insert(term);
            } else {
                res.vars[term.first] += term.second;
            }
        }
        for (auto it = res.vars.begin(); it != res.vars.end();) {
            if (it->second == 0) {
                it = res.vars.erase(it);
            } else {
                ++it;
            }
        }
        res.known_term += known_term;
        return res;
    }

    lin lin::operator+(const double& right) const {
        lin res = *this;
        res.known_term += right;
        return res;
    }

    lin operator+(const double& lhs, const lin& rhs) {
        lin res = rhs;
        res.known_term += lhs;
        return res;
    }

    lin lin::operator-(const lin& right) const {
        lin res = *this;
        for (auto& term : right.vars) {
            if (res.vars.find(term.first) == res.vars.end()) {
                res.vars.insert({term.first, -term.second});
            } else {
                res.vars[term.first] -= term.second;
            }
        }
        for (auto it = res.vars.begin(); it != res.vars.end();) {
            if (it->second == 0) {
                it = res.vars.erase(it);
            } else {
                ++it;
            }
        }
        res.known_term -= right.known_term;
        return res;
    }

    lin lin::operator-(const double& right) const {
        lin res = *this;
        res.known_term -= right;
        return res;
    }

    lin operator-(const double& lhs, const lin& rhs) {
        lin res = -rhs;
        res.known_term += lhs;
        return res;
    }

    lin lin::operator*(const double& right) const {
        lin res = *this;
        for (auto& term : res.vars) {
            term.second *= right;
        }
        res.known_term *= right;
        return res;
    }

    lin operator*(const double& lhs, const lin& rhs) {
        lin res = rhs;
        for (auto& term : res.vars) {
            term.second *= lhs;
        }
        res.known_term *= lhs;
        return res;
    }

    lin lin::operator/(const double& right) const {
        lin res = *this;
        for (auto& term : res.vars) {
            term.second /= right;
        }
        res.known_term /= right;
        return res;
    }

    lin lin::operator+=(const lin& right) {
        for (auto& term : right.vars) {
            if (vars.find(term.first) == vars.end()) {
                vars.insert(term);
            } else {
                vars[term.first] += term.second;
            }
        }
        for (auto it = vars.begin(); it != vars.end();) {
            if (it->second == 0) {
                it = vars.erase(it);
            } else {
                ++it;
            }
        }
        known_term += right.known_term;
        return *this;
    }

    lin lin::operator+=(const std::pair<var, double>& term) {
        if (vars.find(term.first) == vars.end()) {
            vars.insert({term.first, -term.second});
        } else {
            vars[term.first] += term.second;
        }
        if (vars[term.first] == 0) {
            vars.erase(term.first);
        }
        return *this;
    }

    lin lin::operator+=(const double& right) {
        known_term += right;
        return *this;
    }

    lin lin::operator-=(const lin& right) {
        for (auto& term : right.vars) {
            if (vars.find(term.first) == vars.end()) {
                vars.insert({term.first, -term.second});
            } else {
                vars[term.first] -= term.second;
            }
        }
        for (auto it = vars.begin(); it != vars.end();) {
            if (it->second == 0) {
                it = vars.erase(it);
            } else {
                ++it;
            }
        }
        known_term -= right.known_term;
        return *this;
    }

    lin lin::operator-=(const std::pair<var, double>& term) {
        if (vars.find(term.first) == vars.end()) {
            vars.insert({term.first, -term.second});
        } else {
            vars[term.first] -= term.second;
        }
        if (vars[term.first] == 0) {
            vars.erase(term.first);
        }
        return *this;
    }

    lin lin::operator-=(const double& right) {
        known_term -= right;
        return *this;
    }

    lin lin::operator*=(const double& right) {
        for (auto& term : vars) {
            term.second *= right;
        }
        known_term *= right;
        for (auto it = vars.begin(); it != vars.end();) {
            if (it->second == 0) {
                it = vars.erase(it);
            } else {
                ++it;
            }
        }
        return *this;
    }

    lin lin::operator/=(const double& right) {
        for (auto& term : vars) {
            term.second /= right;
        }
        known_term /= right;
        for (auto it = vars.begin(); it != vars.end();) {
            if (it->second == 0) {
                it = vars.erase(it);
            } else {
                ++it;
            }
        }
        return *this;
    }

    lin lin::operator-() const {
        lin res;
        for (auto& term : vars) {
            res.vars[term.first] = -term.second;
        }
        res.known_term = -known_term;
        return res;
    }

    std::ostream& operator<<(std::ostream& os, const lin& obj) {
        if (obj.vars.empty()) {
            os << std::to_string(obj.known_term);
            return os;
        }

        for (std::map<var, double>::const_iterator it = obj.vars.begin(); it != obj.vars.end(); ++it) {
            if (it == obj.vars.begin()) {
                if (it->second == 1) {
                    os << "x" << std::to_string(it->first);
                } else if (it->second == -1) {
                    os << "-x" << std::to_string(it->first);
                } else {
                    os << std::to_string(it->second) << "*x" << std::to_string(it->first);
                }
            } else {
                if (it->second == 1) {
                    os << " + x" << std::to_string(it->first);
                } else if (it->second == -1) {
                    os << " - x" << std::to_string(it->first);
                } else if (it->second > 0) {
                    os << " + " << std::to_string(it->second) << "*x" << std::to_string(it->first);
                } else {
                    os << " - " << std::to_string(-it->second) << "*x" << std::to_string(it->first);
                }
            }
        }

        if (obj.known_term > 0) {
            os << " + " << std::to_string(obj.known_term);
        }
        if (obj.known_term < 0) {
            os << " - " << std::to_string(-obj.known_term);
        }
        return os;
    }
}