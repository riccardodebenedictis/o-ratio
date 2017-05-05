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
 * File:   newsimpletest.cpp
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 *
 * Created on April 15, 2017, 4:34 PM
 */

#include "causal_graph.h"
#include "causal_graph_listener.h"
#include <stdlib.h>
#include <iostream>

/*
 * Simple C++ Test Suite
 */

void testCG0() {
    cg::causal_graph g;
    cg::causal_graph_listener l(g);

    bool rd = g.read(std::vector<std::string>{"tests/test_sv_0.rddl"});
    assert(rd);

    bool slvd = g.solve();
    assert(slvd);

    ratio::expr f0 = g.get("f0");
    ratio::arith_expr f0_start = f0->get("start");
    ratio::arith_expr f0_end = f0->get("end");
    ratio::arith_expr f0_duration = f0->get("duration");

    assert(g.arith_value(f0_start) == 0);
    assert(g.arith_value(f0_end) == 10);
    assert(g.arith_value(f0_duration) == 10);

    ratio::expr g0 = g.get("g0");
    ratio::arith_expr g0_start = g0->get("start");
    ratio::arith_expr g0_end = g0->get("end");
    ratio::arith_expr g0_duration = g0->get("duration");

    assert(g.arith_value(g0_start) == 20);
    assert(g.arith_value(g0_end) == 30);
    assert(g.arith_value(g0_duration) == 10);
}

void testCG1() {
    cg::causal_graph g;
    cg::causal_graph_listener l(g);

    bool rd = g.read(std::vector<std::string>{"tests/test_sv_1.rddl"});
    assert(rd);

    bool slvd = g.solve();
    assert(slvd);
}

void testCG2() {
    cg::causal_graph g;
    cg::causal_graph_listener l(g);

    bool rd = g.read(std::vector<std::string>{"tests/test_sv_2.rddl"});
    assert(rd);

    bool slvd = g.solve();
    assert(slvd);

    ratio::expr f0 = g.get("f0");
    ratio::arith_expr f0_start = f0->get("start");
    ratio::arith_expr f0_end = f0->get("end");
    ratio::arith_expr f0_duration = f0->get("duration");

    assert(g.arith_value(f0_start) == 0);
    assert(g.arith_value(f0_end) == 10);
    assert(g.arith_value(f0_duration) == 10);

    ratio::expr g0 = g.get("g0");
    ratio::arith_expr g0_start = g0->get("start");
    ratio::arith_expr g0_end = g0->get("end");
    ratio::arith_expr g0_duration = g0->get("duration");

    assert(g.arith_value(g0_start) == 10);
    assert(g.arith_value(g0_end) == 20);
    assert(g.arith_value(g0_duration) == 10);
}

void testCG3() {
    cg::causal_graph g;
    cg::causal_graph_listener l(g);

    bool rd = g.read(std::vector<std::string>{"tests/test_sv_3.rddl"});
    assert(rd);

    bool slvd = g.solve();
    assert(slvd);
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% cg_test" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% testCG0 (cg_test)" << std::endl;
    testCG0();
    std::cout << "%TEST_FINISHED% testCG0=0 test1 (cg_test)" << std::endl;

    std::cout << "%TEST_STARTED% testCG1 (cg_test)" << std::endl;
    testCG1();
    std::cout << "%TEST_FINISHED% testCG1=0 test1 (cg_test)" << std::endl;

    std::cout << "%TEST_STARTED% testCG2 (cg_test)" << std::endl;
    testCG2();
    std::cout << "%TEST_FINISHED% testCG2=0 test1 (cg_test)" << std::endl;

    std::cout << "%TEST_STARTED% testCG3 (cg_test)" << std::endl;
    testCG3();
    std::cout << "%TEST_FINISHED% testCG3=0 test1 (cg_test)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

