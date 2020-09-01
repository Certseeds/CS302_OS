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

using std::abs;
using std::cout;
using std::deque;

deque<int32_t> read_datas();

void FCFS(deque<int32_t> track);

void SSTF(deque<int32_t> track);

void SCAN(deque<int32_t> track);

void C_SCAN(deque<int32_t> track);

void LOOK(deque<int32_t> track);

void C_LOOK(deque<int32_t> track);

void output(const char *str, const deque<int32_t> &track, int32_t distance);

/**
 * S represents the position of beginning track.
 * M represents the total number of tracks in disk.
 * N represents the number of scheduling requests.
 */
static int32_t S = 0;
static int32_t M = 0; // max is M-1
static int32_t N = 0;

deque<int32_t> read_datas() {
    std::cin >> S >> M >> N;
    deque<int32_t> track_number = deque<int32_t>(N, 0);
    for (auto &number : track_number) {
        std::cin >> number;
    }
    return track_number;
}

int main() {
    auto track_number = read_datas();
    FCFS(track_number);
    SSTF(track_number);
    SCAN(track_number);
    C_SCAN(track_number);
    LOOK(track_number);
    C_LOOK(track_number);
    return 0;
}

void FCFS(deque<int32_t> track) {
    int32_t last_head = S;
    int32_t distance = 0;
    track.push_front(S);
    for (const auto &item : track) {
        distance += abs(item - last_head);
        last_head = item;
    }
    output("FIFO", track, distance);
}

void SSTF(deque<int32_t> track) {
    deque<int32_t> deq(N + 1, 0);
    deq[0] = S;
    int32_t distance = 0;
    for (uint32_t i = 1; i < deq.size(); ++i) {
        int32_t last = deq[i - 1];
        auto min_p = std::min_element(std::begin(track), std::end(track), [&last](int32_t t1, int32_t t2) {
            return abs(last - t1) < abs(last - t2);
        });
        deq[i] = *min_p;
        distance += abs(deq[i] - last);
        track.erase(min_p);
    }
    output("SSTF", deq, distance);
}

void SCAN(deque<int32_t> track) {
    track.push_front(0);
    track.push_front(S);
    std::sort(std::begin(track), std::end(track), std::less<int32_t>());
    std::queue<int32_t> temp;
    while (track.front() <= S) {
        temp.push(track.front());
        track.pop_front();
    }
    while (!temp.empty()) {
        track.push_front(temp.front());
        temp.pop();
    }
    int32_t distance = 0;
    for (uint32_t i = 0; i < track.size() - 1; ++i) {
        distance += abs(track[i + 1] - track[i]);
    }
    output("SCAN", track, distance);
}

void C_SCAN(deque<int32_t> track) {
    track.push_front(0);
    track.push_front(S);
    track.push_front(M - 1);
    std::sort(std::begin(track), std::end(track), std::less<int32_t>());
    std::queue<int32_t> temp;
    while (track.front() <= S) {
        temp.push(track.front());
        track.pop_front();
    }
    deque<int32_t> temp2;
    for (auto i = track.rbegin(); i != track.rend(); ++i) {
        temp2.push_back(*i);
    }
    while (!temp.empty()) {
        temp2.push_front(temp.front());
        temp.pop();
    }
    int32_t distance = 0;
    for (uint32_t i = 0; i < temp2.size() - 1; ++i) {
        distance += abs(temp2[i + 1] - temp2[i]);
    }
    // update in 20200603, 需要计算扫描完跳回去的距离.
    // TODO distance 不知道要不要加头->尾
    output("C_SCAN", temp2, distance);
}

void LOOK(deque<int32_t> track) {
    track.push_front(S);
    std::sort(std::begin(track), std::end(track), std::less<int32_t>());
    std::queue<int32_t> temp;
    while (track.front() <= S) {
        temp.push(track.front());
        track.pop_front();
    }
    while (!temp.empty()) {
        track.push_front(temp.front());
        temp.pop();
    }
    int32_t distance = 0;
    for (uint32_t i = 0; i < track.size() - 1; ++i) {
        distance += abs(track[i + 1] - track[i]);
    }
    output("LOOK", track, distance);
}

// TODO, needed is only C_LOOK algorith.
// BUT i only get 26/40 scores, why?
// IF you know why, please create issue for repo.
void C_LOOK(deque<int32_t> track) {
    // TODO , infact, distance of lowest back to highest is hard to decide to calcaute or not.
    // this refer the example.in.txt and example.out.txt.
    std::sort(std::begin(track), std::end(track), std::greater<int32_t>());
    int32_t dis = S + 2 * track.front() - 2 * track.back();
    while (track.back() <= S) {
        track.push_front(track.back());
        track.pop_back();
    }
    track.push_front(S);
    dis -= track.back();
    output("C_LOOK", track, dis);
}

void output(const char *str, const deque<int32_t> &track, int32_t distance) {
    cout << str << " \n";
    for (uint32_t i = 0; i < track.size() - 1; i++) {
        cout << track[i] << " ";
    }
    cout << track.back() << "\n";
    cout << distance << "\n";
}