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
 * @Date: 2020-04-13 19:19:15 
 * @LastEditors  : nanoseeds
 */
// 原始版只拿到了40分中的20分.
// 这个版本不保证正确性.
#include <deque>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "Banker_struct.hpp"

using std::cin;
using std::cout;
using std::deque;
using std::endl;
using std::string;
using std::unordered_map;
using std::vector;
using input_data_tuple = std::tuple<vector<int32_t>, vector<command>>;
static int32_t r{0};

input_data_tuple read_from_io();

deque<bool> banker_algorithm(const input_data_tuple &input);

bool judge_request(vector<int32_t> resource, const command &com, unordered_map<int32_t, process> u_process);

void do_request(const command &com, vector<int32_t> &resource, unordered_map<int32_t, process> &u_process);

void output_OK(const deque<bool> &deq);

void main2();

input_data_tuple read_from_io() {
    std::cin >> r;
    vector<int32_t> resource(r, 0);
    for (auto &i : resource) {
        std::cin >> i;
    }
    int32_t process_id{0};
    vector<command> vec_command;
    while (std::cin >> process_id) {
        string command_input;
        std::cin >> command_input;
        command command_this = command(name_to_type(command_input), process_id, r);
        switch (command_this.command_type) {
            case COMMAND_TYPE::NEW:
            case COMMAND_TYPE::REQUEST: {
                for (auto &i : command_this.resource) {
                    std::cin >> i;
                }
                break;
            }
            case COMMAND_TYPE::TERMINATE: {
                break;
            }
        }
        vec_command.push_back(command_this);
    }
    return input_data_tuple(resource, vec_command);
}

deque<bool> banker_algorithm(const input_data_tuple &input) {
    vector<int32_t> resource;
    vector<command> commands;
    std::tie(resource, commands) = input;
    const vector<int32_t> max_resource(resource);
    //int32_t resource_size = resource.size();
    deque<bool> deq;
    unordered_map<int32_t, process> u_process;
    for (const auto &item : commands) {
        switch (item.command_type) {
            case COMMAND_TYPE::NEW: {
                // 只判断能不能new出来 // can not find -> true
                bool can_alloc = (u_process.find(item.process_id) == std::end(u_process));
                for (auto i = 0; can_alloc && i < r; ++i) {
                    can_alloc = (max_resource[i] >= item.resource[i]);
                }
                if (can_alloc) {
                    u_process[item.process_id] = process(item.process_id, item.resource);
                }
                deq.push_back(can_alloc);
                break;
            }
            case COMMAND_TYPE::REQUEST: {
                bool can_find_process = (u_process.find(item.process_id) != std::end(u_process));
                bool can_request = can_find_process && judge_request(resource, item, u_process);
                if (can_request) {
                    do_request(item, resource, u_process);
                }
                deq.push_back(can_request);
                break;
            }
            case COMMAND_TYPE::TERMINATE: {
                // can find is true
                bool find_or_not = u_process.find(item.process_id) != std::end(u_process);
                if (find_or_not) {
                    for (auto i = 0; i < r; ++i) {
                        resource[i] += u_process[item.process_id].alloc_resource[i];
                        //this_process.alloc_resource[i] = 0;
                    }
                    //this_process.needed_resource = this_process.max_resource;
                    u_process.erase(item.process_id);
                }
                deq.push_back(find_or_not);
                break;
            }
        }
    }
    return deq;
}

bool
judge_request(vector<int32_t> resource, const command &com, unordered_map<int32_t, process> u_process) {
    int32_t id = com.process_id;
    process &pro = u_process[id];
    for (int32_t i = 0; i < r; ++i) {
        if (com.resource[i] > pro.needed_resource[i]
            || resource[i] < com.resource[i]) {
            return false;
        }
    }
    // now, it at least can let the process do it's request success.
    // 因为是copy过来的,所以没问题.
    do_request(com, resource, u_process);
    // do action on the copyed resource.
    unordered_map<int32_t, bool> finish;
    for (const auto &item : u_process) {
        finish[item.first] = false;
    }
    bool jump_out;
    for (int32_t i = 0; i < u_process.size(); ++i) {
        jump_out = false;
        for (const auto &item : u_process) {
            if (!finish[item.first]) {
                bool jump_in = true;
                for (int j = 0; j < r; ++j) {
                    if (item.second.needed_resource[j] > resource[j]) {
                        jump_in = false;
                        break;
                    }
                }
                if (jump_in) {
                    jump_out = true;
                    for (int j = 0; j < r; ++j) {
                        resource[j] += item.second.alloc_resource[j];
                    }
                    finish[item.first] = true;
                }
            }
        }
        if (!jump_out) {
            break;
        }
    }
    jump_out = true;
    for (const auto &item1 : finish) {
        jump_out = jump_out && item1.second;
    }
    return jump_out;
}

void do_request(const command &com, vector<int32_t> &resource, unordered_map<int32_t, process> &u_process) {
    int32_t id = com.process_id;
    for (int i = 0; i < r; ++i) {
        u_process[id].alloc_resource[i] += com.resource[i];
        u_process[id].needed_resource[i] -= com.resource[i];
        resource[i] -= com.resource[i];
    }
}

void output_OK(const deque<bool> &deq) {
    const string next_line = "\n";
    const vector<string> words{"NOT OK" + next_line, "OK" + next_line};
    for (const auto &i : deq) {
        // false -> not ok
        // true -> ok
        std::cout << words[i];
    }
}

void main2() {
    auto input_data = read_from_io();
    auto output_data = banker_algorithm(input_data);
    output_OK(output_data);
};

#ifndef CS302_OS_TEST_MACRO
#define CS302_OS_TEST_MACRO
int main() {
    main2();
}
#endif  //CS302_OS_TEST_MACRO
