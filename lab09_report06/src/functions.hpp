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
 * @Date: 2020-05-03 18:18:16 
 * @LastEditors  : nanoseeds
 */
#ifndef CS302_OS_LAB09_REPORT06_SRC_FUNCTIONS_HPP
#define CS302_OS_LAB09_REPORT06_SRC_FUNCTIONS_HPP

#include "allocated_block.hpp"
#include "free_block.hpp"
#include <unordered_map>
#include <functional>

using std::unordered_map;
enum algorithm_code {
    BF = 1, WF = 2, FF = 3, BS = 4
};
// 负责每次循环后,将相邻的free_block merge到一起.(还有一部分merge在free_mem)时做了
auto cmp_BF = [](const free_block *const f1, const free_block *const f2) -> bool {
    return f1->size < f2->size;
};
auto cmp_WF = [](const free_block *const f1, const free_block *const f2) -> bool {
    return f1->size > f2->size;
};
auto cmp_FF = [](const free_block *const f1, const free_block *const f2) -> bool {
    return f1->start_addr < f2->start_addr;
};
unordered_map<algorithm_code,
        std::function<bool(const free_block *const f1,
                           const free_block *const f2)>> cmp
        = {{BF, cmp_BF},
           {WF, cmp_WF},
           {FF, cmp_FF},
           {BS, cmp_BF}};


#endif //CS302_OS_LAB09_REPORT06_SRC_FUNCTIONS_HPP