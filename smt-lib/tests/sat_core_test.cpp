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
 * File:   sat_core_test.cpp
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 *
 * Created on April 10, 2017, 4:45 PM
 */

#include "../sat_core.h"
#include <stdlib.h>
#include <iostream>
#include <cassert>

/*
 * Simple C++ Test Suite
 */

using namespace smt;

void testSAT0() {
    sat_core c;

    var b0 = c.new_var();
    var b1 = c.new_var();
    var b2 = c.new_var();
    var b3 = c.new_var();
    var b4 = c.new_var();
    var b5 = c.new_var();
    var b6 = c.new_var();
    var b7 = c.new_var();
    var b8 = c.new_var();

    bool cs;
    cs = c.new_clause({lit(b0, true), lit(b1, true)});
    assert(cs);
    cs = c.new_clause({lit(b0, true), lit(b2, true), lit(b6, true)});
    assert(cs);
    cs = c.new_clause({lit(b1, false), lit(b2, false), lit(b3, true)});
    assert(cs);
    cs = c.new_clause({lit(b3, false), lit(b4, true), lit(b7, true)});
    assert(cs);
    cs = c.new_clause({lit(b3, false), lit(b5, true), lit(b8, true)});
    assert(cs);
    cs = c.new_clause({lit(b4, false), lit(b5, false)});
    assert(cs);

    bool a;
    a = c.assume(lit(b6, false)) && c.check();
    assert(a);
    a = c.assume(lit(b7, false)) && c.check();
    assert(a);
    a = c.assume(lit(b8, false)) && c.check();
    assert(a);
    a = c.assume(lit(b0, false)) && c.check();
    assert(a);
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% sat_core_test" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% testSAT0 (sat_core_test)" << std::endl;
    testSAT0();
    std::cout << "%TEST_FINISHED% time=0 testSAT0 (sat_core_test)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

