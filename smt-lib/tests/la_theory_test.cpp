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
 * File:   la_theory_test.cpp
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 *
 * Created on April 11, 2017, 2:51 PM
 */

#include "../sat_core.h"
#include "../la_theory.h"
#include <stdlib.h>
#include <iostream>
#include <cassert>

/*
 * Simple C++ Test Suite
 */

using namespace smt;

void testLA0() {
    sat_core c;
    la_theory la(c);

    var x0 = la.new_var();
    var x1 = la.new_var();

    var leq_0 = la.leq(lin(x0, 1), lin(-4));
    var geq_0 = la.geq(lin(x0, 1), lin(-8));
    var leq_1 = la.leq(lin(x0, -1) + lin(x1, 1), lin(1));
    var geq_1 = la.geq(lin(x0, 1) + lin(x1, 1), lin(-3));

    bool a;
    a = c.assume(lit(leq_0, true)) && c.check();
    assert(a);
    a = c.assume(lit(geq_0, true)) && c.check();
    assert(a);
    a = c.assume(lit(leq_1, true)) && c.check();
    assert(a);
    a = c.assume(lit(geq_1, true)) && c.check();
    assert(a);
}

void testLA1() {
    sat_core c;
    la_theory la(c);

    var b0 = c.new_var();
    var x0 = la.new_var();

    var b5 = la.geq(lin(x0, 1), lin(10));
    var b6 = la.leq(lin(x0, 1), lin(0));

    bool cs;
    cs = c.new_clause({lit(b0, false), lit(b5, true)});
    assert(cs);
    cs = c.new_clause({lit(b5, false), lit(b6, true)});
    assert(cs);

    bool p = c.check();
    assert(p);

    bool a;
    a = c.assume(lit(b0, true)) && c.check();
    assert(a);
}

void testTheoryPropagation() {
    sat_core c;
    la_theory la(c);

    var x0 = la.new_var();
    var b2 = la.geq(lin(x0, 1), lin(1));
    var b3 = la.geq(lin(x0, 1), lin(0));
    var b4 = la.leq(lin(x0, 1), lin(-1));

    bool a;
    a = c.assume(lit(b2, true)) && c.check();
    assert(a);
    assert(c.value(b3) == True);
    assert(c.value(b4) == False);

    var x1 = la.new_var();
    var b5 = la.leq(lin(x1, 1), lin(-1));
    var b6 = la.leq(lin(x1, 1), lin(0));
    var b7 = la.geq(lin(x1, 1), lin(1));

    a = c.assume(lit(b5, true)) && c.check();
    assert(a);
    assert(c.value(b6) == True);
    assert(c.value(b7) == False);
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% la_theory_test" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% testLA0 (la_theory_test)" << std::endl;
    testLA0();
    std::cout << "%TEST_FINISHED% time=0 testLA0 (la_theory_test)" << std::endl;

    std::cout << "%TEST_STARTED% testLA1 (la_theory_test)" << std::endl;
    testLA1();
    std::cout << "%TEST_FINISHED% time=0 testLA1 (la_theory_test)" << std::endl;

    std::cout << "%TEST_STARTED% testTheoryPropagation (la_theory_test)" << std::endl;
    testTheoryPropagation();
    std::cout << "%TEST_FINISHED% time=0 testTheoryPropagation (la_theory_test)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

