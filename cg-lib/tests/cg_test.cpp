/*
 * Copyright (C) 2017 sydde
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
 * Author: sydde
 *
 * Created on April 15, 2017, 4:34 PM
 */

#include "causal_graph.h"
#include <stdlib.h>
#include <iostream>

/*
 * Simple C++ Test Suite
 */

void testCG0() {
    cg::causal_graph g;

    bool rd = g.read(std::vector<std::string>{"tests/test_sv_0.rddl"});
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

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

