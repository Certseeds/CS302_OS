/**
 * @Github: https://github.com/Certseeds/CS302_OS
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2020-08-03 22:10:22
 * @LastEditors  : nanoseeds
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
#ifndef CS302_OS_INCLUDE_PUBLIC_H
#define CS302_OS_INCLUDE_PUBLIC_H

#include <string>
#include <fstream>
#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <algorithm>
#include "CS302_timer.hpp"
#include "CS302_redirect.hpp"

using std::ios;
using std::cin;
using std::cout;
CS302_timer timer{};

static int faster_streams = []() {
    srand(time(0));
    // use time to init the random seed
    std::ios::sync_with_stdio(false);
    std::istream::sync_with_stdio(false);
    std::ostream::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    // 关闭c++风格输入输出 , 与C风格输入输出的同步,提高性能.
    return 0;
}();

bool compareFiles(const std::string &p1, const std::string &p2) {
    // get from https://stackoverflow.com/questions/6163611/compare-two-files
    std::ifstream f1(p1, std::ifstream::binary | std::ifstream::ate);
    std::ifstream f2(p2, std::ifstream::binary | std::ifstream::ate);
    if (f1.fail() || f2.fail()) {
        return false; //file problem
    }
    if (f1.tellg() != f2.tellg()) {
        std::cout << p1 << " not match " << p2 << '\n';
        std::cout << f1.tellg() << " " << f2.tellg() << '\n';
        return false; //size mismatch
    }
    //seek back to beginning and use std::equal to compare contents
    f1.seekg(0, std::ifstream::beg);
    f2.seekg(0, std::ifstream::beg);
    return std::equal(std::istreambuf_iterator<char>(f1.rdbuf()),
                      std::istreambuf_iterator<char>(),
                      std::istreambuf_iterator<char>(f2.rdbuf()));
}

#endif //CS302_OS_INCLUDE_PUBLIC_H
