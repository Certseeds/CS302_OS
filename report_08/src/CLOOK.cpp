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
#include <queue>
#include <iostream>
#include <algorithm>

void read_datas();

void C_LOOK();

void output();

/**
 * S represents the position of beginning track.
 * M represents the total number of tracks in disk.
 * N represents the number of scheduling requests.
 */
static int32_t S = 0;
static int32_t M = 0;
static int32_t N = 0;
static std::deque<int32_t> track_number;
static int32_t dis = 0;

void read_datas() {
    std::cin >> S >> M >> N;
    track_number = std::deque<int32_t>(N, 0);
    for (auto &number : track_number) {
        std::cin >> number;
    }
}

int main() {
    read_datas();
    C_LOOK();
    output();
    return 0;
}

void C_LOOK() {
    std::sort(std::begin(track_number), std::end(track_number), std::greater<int32_t>());
    dis = S + 2 * track_number.front() - 2 * track_number.back();
    while (track_number.back() <= S) {
        track_number.push_front(track_number.back());
        track_number.pop_back();
    }
    track_number.push_front(S);
    dis -= track_number.back();
}

void output() {
    for (int32_t i = 0; i < N; i++) {
        std::cout << track_number[i] << " ";
    }
    std::cout << track_number.back() << "\n";
    std::cout << dis;
}