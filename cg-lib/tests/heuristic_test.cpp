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
 * File:   heuristic_test.cpp
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 *
 * Created on April 28, 2017, 3:35 PM
 */

#include "causal_graph.h"
#include <stdlib.h>
#include <iostream>

/*
 * Simple C++ Test Suite
 */

void test_heuristic_failure_0() {
    cg::causal_graph g;

    bool rd = g.read(std::vector<std::string>{"tests/test_heuristic_failure_0.rddl"});
    assert(rd);

    bool slvd = g.solve();
    assert(!slvd);
}

void test_heuristic_failure_1() {
    cg::causal_graph g;

    bool rd = g.read(std::vector<std::string>{"tests/test_heuristic_failure_1.rddl"});
    assert(rd);

    bool slvd = g.solve();
    assert(!slvd);
}

void test_heuristic_failure_2() {
    cg::causal_graph g;

    bool rd = g.read(std::vector<std::string>{"tests/test_heuristic_failure_2.rddl"});
    assert(rd);

    bool slvd = g.solve();
    assert(!slvd);
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% heuristic_test" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% test_heuristic_failure_0 (heuristic_test)" << std::endl;
    test_heuristic_failure_0();
    std::cout << "%TEST_FINISHED% time=0 test_heuristic_failure_0 (heuristic_test)" << std::endl;

    std::cout << "%TEST_STARTED% test_heuristic_failure_1 (heuristic_test)" << std::endl;
    test_heuristic_failure_1();
    std::cout << "%TEST_FINISHED% time=0 test_heuristic_failure_1 (heuristic_test)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

