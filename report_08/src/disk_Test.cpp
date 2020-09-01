/*
 * @Github: https://github.com/Certseeds/CS302_OS
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2020-08-04 11:07:33
 * @LastEditors: nanoseeds
 * @LastEditTime: 2020-08-23 16:40:04
 */
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

#include "catch_main.hpp"
#include "disk.cpp"

#include <iostream>
#include <tuple>
#include <vector>

using Catch::Matchers::Contains;
using Catch::Matchers::Equals;
using Catch::Matchers::UnorderedEquals;
using std::string;
using std::tie;
using std::tuple;
using std::vector;
string CS302_redirect::file_paths = "./../../../report_08/data/";
auto files_tuple = [] {
    const static vector<string> datas{"00", "01", "02", "03", "04", "05", "06", "07", "08", "09"};
    std::vector<std::tuple<string, string, string>> files;
    for (const auto &i : datas) {
        files.push_back(std::make_tuple<string, string, string>(
                i + ".data.in",
                i + ".data.out",
                i + ".test.out"));
    }
    return files;
};

TEST_CASE("test case 1", "[Banker]") {
    SECTION("do") {
        CS302_redirect cr{"00.data.in", "00.test.out"};
        auto input = read_from_io();
        auto output = banker_algorithm(input);
        output_OK(output);
    }SECTION("compare files") {
        CHECK(compareFiles("00.data.out", "00.test.out"));
    }
}

TEST_CASE("test case all", "[Banker]") {
    for (const auto &i : files_tuple()) {
        string input_file;
        string output_file;
        string test_output_file;
        tie(input_file, output_file, test_output_file) = i;
        {
            CS302_redirect cr{input_file, test_output_file};
            main2();
        }
        CHECK(compareFiles(output_file, test_output_file));
    }
}

#endif  // CS302_OS_TEST_MACRO