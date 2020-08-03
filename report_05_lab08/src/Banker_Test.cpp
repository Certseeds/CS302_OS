/*  CS302_OS 
    Copyright (C) 2020  nanoseeds

    CS302_OS is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as
    published by the Free Software Foundation, either version 3 of the
    License, or (at your option) any later version.

    CS302_OS is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
    */
/**
 * @Github: https://github.com/Certseeds/CS302_OS
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2020-08-03 22:17:55 
 * @LastEditors  : nanoseeds
 */
#ifndef CS302_OS_TEST_MACRO
#define CS302_OS_TEST_MACRO

#include <tuple>
#include <vector>
#include <iostream>
#include "catch_main.hpp"
#include "Banker.cpp"

using Catch::Matchers::Equals;
using Catch::Matchers::UnorderedEquals;
using Catch::Matchers::Contains;
const string test_file_path = "./../../../report_05_lab08/data/";

TEST_CASE("test case 1", "[Banker]") {
    SECTION("do") {
        CS302_redirect cr{test_file_path + "Sample0.in", test_file_path + "Sample0.test.out"};
        auto temp = read_from_io();
        int x = 1;
    }SECTION("compare files") {
        //    CHECK(compareFiles(test_file_path + "Sample0.test.out", test_file_path + "Sample0.out"));
    }
}

#endif // CS302_OS_TEST_MACRO