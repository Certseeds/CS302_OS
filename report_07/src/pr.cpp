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
 * @Date: 2020-05-09 21:54:33
 * @LastEditors  : nanoseeds
 */
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("fast-math")
#pragma GCC optimize("inline")
#pragma GCC target("avx,avx2,sse,sse2")

#include <list>
#include <queue>
#include <cmath>
#include <vector>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <functional>
#include <unordered_map>

using std::cout;
using std::cin;
using std::pair;
using std::vector;
const static std::string end = "\n";
static int32_t faster_streams = []() {
    std::ios::sync_with_stdio(false);
    std::istream::sync_with_stdio(false);
    std::ostream::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 0;
}();

inline void read_input();

void FIFO_F();

void LRU_F();

void MIN_F();

void CLOCK_F();

void SECOND_CHANCE_F();

enum Algorithm {
    FIFO = 0, LRU = 1, MIN = 2, CLOCK = 3, SECOND_CHANCE = 4
};

static size_t cache_size = 0;
static Algorithm algorithm = FIFO;
static int32_t query_numbers = 0;
static std::vector<int32_t> query_pages;
static int32_t hit = 0;
static std::unordered_map<Algorithm, std::function<void()>> umap = {
        {FIFO,          FIFO_F},
        {LRU,           LRU_F},
        {MIN,           MIN_F},
        {CLOCK,         CLOCK_F},
        {SECOND_CHANCE, SECOND_CHANCE_F}};

// TODO, this do not get any scores, i do not know why.
// If you know, please create issues.
int main() {
    read_input();
    umap[algorithm]();
    cout << "Hit ratio = " << std::fixed << std::setprecision(2) <<
         std::ceil(10000.0f * (hit * 1.0f / query_numbers)) / 100.0f << "%" << end;
    return 0;
}


void FIFO_F() {
    std::deque<int32_t> deque_fifo;
    for (const auto &i:query_pages) {
        if (std::find(deque_fifo.begin(), deque_fifo.end(), i) != std::end(deque_fifo)) {
            hit++;
        } else {
            if (deque_fifo.size() == cache_size) {
                deque_fifo.pop_front();
            }
            deque_fifo.push_back(i);
        }
    }
}

void LRU_F() {
    std::list<int32_t> list_lru;
    size_t list_size = 0;
    for (int32_t j = 0; j < query_numbers; ++j) {
        int32_t pq = query_pages[j];
        auto result = std::find(std::begin(list_lru), std::end(list_lru), pq);
        if (result != std::end(list_lru)) {
            hit++;
            list_lru.erase(result);
            list_lru.push_front(pq);
        } else {
            if (list_size == cache_size) {
                list_lru.pop_back();
                list_size--;
            }
            list_lru.push_front(pq);
            list_size++;
        }
    }
}

void MIN_F() {
    // TODO need fix, now it can not output correct.
    vector<pair<int32_t, int32_t>> u_page;
    for (uint32_t i = 0; i < query_pages.size(); i++) {
        int32_t iter = query_pages[i];
        query_pages[i] = 0;
        auto result = std::find_if(u_page.begin(), u_page.end(), [&iter](
                const pair<int32_t, int32_t> p1) { return p1.first == iter; });
        if (result != std::end(u_page)) {
            hit++;
            cout << i << " " << iter << end;
        } else {
            if (u_page.size() == cache_size) {
                auto min_v = std::max_element(u_page.begin(), u_page.end(),
                                              [](const pair<int32_t, int32_t> p1,
                                                 const pair<int32_t, int32_t> p2) {
                                                  return p1.second < p2.second;
                                              });
                u_page.erase(min_v);
                cout.flush();
            }
            u_page.emplace_back(iter,
                                std::distance(query_pages.begin(),
                                              std::find(query_pages.begin() + 1,
                                                        query_pages.end(),
                                                        iter)));
        }
    }
}

void CLOCK_F() {
    vector<pair<int32_t, bool>> vec_p(cache_size, std::make_pair(-1, 0));
    int32_t head = 0;
    for (const auto &pq : query_pages) {
        auto find = std::find_if(vec_p.begin(), vec_p.end(), [&pq](
                const std::pair<int32_t, int32_t> p1) { return p1.first == pq; });
        if (find != vec_p.end()) {
            find->second = true;
            hit++;
        } else {
            for (size_t k = 0, j = head; k < cache_size + 1; ++k, j++, j = j % cache_size) {
                if (vec_p[j % cache_size].second) {
                    vec_p[j % cache_size].second = false;
                } else {
                    vec_p[j % cache_size] = std::make_pair(pq, true);
                    j++;
                    j %= cache_size;
                    head = j;
                    break;
                }
            }
        }
    }
}

void SECOND_CHANCE_F() {
    size_t list_lru_size_count = 0;
    size_t list_size = cache_size / 2;
    size_t u_page_size = cache_size - list_size;
    std::deque<int32_t> deque_fifo; // FIFO , new
    std::deque<int32_t> list_lru;
    //std::unordered_map<int32_t, int32_t> u_page; // LRU, old
    for (int32_t j = 0; j < query_numbers; ++j) {
        int32_t pq = query_pages[j];
        // in fifo
        //auto result = std::find(std::begin(list), std::end(list), pq);
        auto result = std::find(std::begin(deque_fifo), std::end(deque_fifo), pq);
        if (result != std::end(deque_fifo)) {
            hit++;
            continue;
        }
        // in lru
        auto result2 = std::find(std::begin(list_lru), std::end(list_lru), pq);
        if (result2 != std::end(list_lru)) {
            hit++;
            list_lru.erase(result2);
            list_lru_size_count--;
            if (deque_fifo.size() == list_size) {
                list_lru.push_front(deque_fifo.front());
                deque_fifo.pop_front();
                list_lru_size_count++;
            }
            deque_fifo.push_back(pq);
            continue;
        }
        // do not in any one.
        if (deque_fifo.size() == list_size) {
            if (list_lru_size_count == u_page_size) {
                list_lru.pop_back();
                list_lru_size_count--;
            }
            list_lru.push_front(deque_fifo.front());
            deque_fifo.pop_front();
            list_lru_size_count++;
        }
        deque_fifo.push_back(pq);
    }
}

void SECOND_CHANCE_F_another_way() {
    std::deque<pair<int32_t, bool>> lp;
    size_t lp_size = 0;
    int32_t temp = 0;
    for (int32_t i = 0; i < query_numbers; ++i) {
        int32_t pq = query_pages[i];
        auto result = std::find_if(std::begin(lp), std::end(lp),
                                   [& pq](const std::pair<int32_t, bool> &p1) { return pq == p1.first; });
        if (result != std::end(lp)) {
            hit++;
            cout << "before " << result->second << end;
            result->second = true;
            cout << "after " << result->second << end;

        } else {
            if (lp_size == cache_size) {
                for (size_t j = 0; j < cache_size + 1; ++j) {
                    if (lp.front().second) {
                        temp = lp.front().first;
                        lp.pop_front();
                        lp.emplace_back(temp, 0);
                    } else {
                        cout << j << end;
                        lp.pop_front();
                        break;
                    }
                }
                lp_size--;
            }
            lp.emplace_back(pq, false);
            lp_size++;
        }
    }
}

inline void read_input() {
    cin >> cache_size;
    int32_t algorithm_number;
    cin >> algorithm_number;
    algorithm = static_cast<Algorithm>(algorithm_number);
    cin >> query_numbers;
    query_pages.reserve(query_numbers);
    int32_t temp_number;
    for (int32_t i = 0; i < query_numbers; ++i) {
        cin >> temp_number;
        query_pages.push_back(temp_number);
    }
}
