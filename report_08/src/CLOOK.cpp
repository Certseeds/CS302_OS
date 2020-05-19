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
 * @Date: 2020-05-19 10:39:17 
 * @LastEditors  : nanoseeds
 */
#include <vector>
#include <iostream>

int main() {
    int32_t S = 0;
    int32_t M = 0;
    int32_t N = 0;
    std::cin >> S >> M >> N;
    std::vector<int32_t> track_number(N, 0);
    for (auto &number : track_number) {
        std::cin >> number;
    }
    return 0;
}