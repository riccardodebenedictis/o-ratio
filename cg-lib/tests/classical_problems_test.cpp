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
 * File:   classical_problems_test.cpp
 * Author: Riccardo De Benedictis <riccardo.debenedictis@istc.cnr.it>
 *
 * Created on May 17, 2017, 5:51 PM
 */

#include "causal_graph.h"
#include "causal_graph_listener.h"
#include <stdlib.h>
#include <iostream>

/*
 * Simple C++ Test Suite
 */

void test_blocks_2() {
    cg::causal_graph g;
    cg::causal_graph_listener l(g);

    bool rd = g.read(std::vector<std::string>{"tests/blocks_2.rddl"});
    assert(rd);

    bool slvd = g.solve();
    assert(slvd);
}

void test_blocks_3() {
    cg::causal_graph g;
    cg::causal_graph_listener l(g);

    bool rd = g.read(std::vector<std::string>{"tests/blocks_3.rddl"});
    assert(rd);

    bool slvd = g.solve();
    assert(slvd);
}

void test_blocks_4() {
    cg::causal_graph g;
    cg::causal_graph_listener l(g);

    bool rd = g.read(std::vector<std::string>{"tests/blocks_4.rddl"});
    assert(rd);

    bool slvd = g.solve();
    assert(slvd);
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% classical_problems_test" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% test_blocks_2 (classical_problems_test)" << std::endl;
    test_blocks_2();
    std::cout << "%TEST_FINISHED% time=0 test_blocks_2 (classical_problems_test)" << std::endl;

    std::cout << "%TEST_STARTED% test_blocks_3 (classical_problems_test)" << std::endl;
    test_blocks_3();
    std::cout << "%TEST_FINISHED% time=0 test_blocks_3 (classical_problems_test)" << std::endl;

    std::cout << "%TEST_STARTED% test_blocks_4 (classical_problems_test)" << std::endl;
    test_blocks_4();
    std::cout << "%TEST_FINISHED% time=0 test_blocks_4 (classical_problems_test)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

