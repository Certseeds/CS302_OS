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
// TODO, 只拿到了40分中的20分.
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
std::tuple<vector<int32_t>, vector<command>> read_from_io();

deque<bool> banker_algorithm(std::tuple<vector<int32_t>, vector<command>> input);

void output_OK(const deque<bool> &deq);
// bool banker_juede(
//     vector<int32_t> resource,
//     unordered_map<int32_t, vector<int32_t>> process_max,
//     unordered_map<int32_t, vector<int32_t>> process_alloca,
//     const vector<int32_t> &need,
//     int32_t process_id);

std::tuple<vector<int32_t>, vector<command>> read_from_io() {
    int32_t r{0};
    std::cin >> r;
    vector<int32_t> resource(r, 0);
    for (auto &i : resource) {
        std::cin >> i;
    }
    int32_t process_id{0};
    vector<command> vec_command;
    while (std::cin >> process_id) {
        command command_this = command(r);
        command_this.process_id = process_id;
        string command_input;
        std::cin >> command_input;
        command_this.command_type = name_to_type(command_input);
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
            case COMMAND_TYPE::NONE: {
                exit(-1);
            }
        }
        vec_command.push_back(command_this);
    }
    return std::tuple<vector<int32_t>, vector<command>>(resource, vec_command);
}

deque<bool> banker_algorithm(std::tuple<vector<int32_t>, vector<command>> input) {
    vector<int32_t> resource;
    vector<command> commands;
    std::tie(resource, commands) = input;
    const vector<int32_t> max_resource(resource);
    int32_t resource_size = resource.size();
    deque<bool> deq;
    unordered_map<int32_t, process> u_process;
    for (const auto &item : commands) {
        switch (item.command_type) {
            case COMMAND_TYPE::NEW: {
                // 只判断能不能new出来
                bool can_alloc = (u_process.find(item.process_id) == std::end(u_process));  // can not find -> true
                for (auto i = 0; i < resource_size && can_alloc; ++i) {
                    can_alloc = can_alloc && (max_resource[i] >= item.resource[i]);
                }
                if (can_alloc) {
                    u_process[item.process_id] = process(item.process_id, item.resource);
                }
                deq.push_back(can_alloc);
                break;
            }
            case COMMAND_TYPE::REQUEST: {
                break;
            }
            case COMMAND_TYPE::TERMINATE: {
                // can find is true
                if (u_process.find(item.process_id) != std::end(u_process)) {
                    for (auto i = 0; i < resource_size; ++i) {
                        resource[i] += u_process[item.process_id].alloc_resource[i];
                        //this_process.alloc_resource[i] = 0;
                    }
                    //this_process.needed_resource = this_process.max_resource;
                    u_process.erase(item.process_id);
                }
                deq.push_back(u_process.find(item.process_id) != std::end(u_process));
                break;
            }
        }
    }
}
void output_OK(const deque<bool> &deq) {
    const string next_line = "\n";
    const vector<string> words{"NOT OK", "OK"};
    for (const auto &i : deq) {
        // false -> not ok
        // true -> ok
        std::cout << words[i] << next_line;
    }
}
#ifndef CS302_OS_TEST_MACRO
#define CS302_OS_TEST_MACRO
int main() {
    auto input_data = read_from_io();
    auto output_data = banker_algorithm(input_data);
    output_OK(output_data);
    return 0;
}
// int main_ {
//     int32_t items = 0;
//     cin >> items;
//     vector<int32_t> resources(items, 0);
//     unordered_map<int32_t, vector<int32_t>> process_max;
//     unordered_map<int32_t, vector<int32_t>> process_alloca;
//     for (int32_t i = 0; i < items; ++i) {
//         cin >> resources[i];
//     }
//     int32_t process_id = 0;
//     while (cin >> process_id) {
//         string action;
//         cin >> action;
//         bool output_ok = true;
//         if ("new" == action) {
//             vector<int32_t> max_re(items, 0);
//             for (int32_t i = 0; i < items; ++i) {
//                 cin >> max_re.at(i);
//             }
//             for (int32_t i = 0; i < items; ++i) {
//                 if (max_re.at(i) > resources.at(i)) {
//                     output_ok = false;
//                 }
//             }
//             if (output_ok) {
//                 process_max[process_id] = max_re;
//                 process_alloca[process_id] = vector<int32_t>(items, 0);
//             }
//         } else if ("request" == action) {
//             vector<int32_t> need(items, 0);
//             for (int32_t i = 0; i < items; ++i) {
//                 cin >> need.at(i);
//             }
//             if (0 == process_max.count(process_id)) {
//                 output_ok = false;
//                 break;
//             }
//             for (int32_t i = 0; i < items; ++i) {
//                 if (need.at(i) > process_max[process_id].at(i) || need.at(i) > resources.at(i)) {
//                     output_ok = false;
//                     break;
//                 }
//             }
//             if (output_ok && banker_juede(resources, process_max, process_alloca, need, process_id)) {
//                 for (int32_t i = 0; i < items; ++i) {
//                     resources[i] -= need[i];
//                     process_max[process_id][i] -= need[i];
//                     process_alloca[process_id][i] += need[i];
//                 }
//             } else {
//                 output_ok = false;
//             }
//         } else if ("terminate" == action) {
//             if (0 == process_max.count(process_id)) {
//                 output_ok = false;
//                 break;
//             }
//             for (int32_t i = 0; i < items; ++i) {
//                 resources[i] += process_alloca[process_id][i];
//             }
//             process_max.erase(process_id);
//             process_alloca.erase(process_id);
//         }
//         if (output_ok) {
//             cout << "OK" << endl;
//         } else {
//             cout << "NOT OK" << endl;
//         }
//     }
//     return 0;
// }

#endif  //CS302_OS_TEST_MACRO

// bool banker_juede(
//     vector<int32_t> resource,
//     unordered_map<int32_t, vector<int32_t>> process_max,
//     unordered_map<int32_t, vector<int32_t>> process_alloca,
//     const vector<int32_t> &need,
//     int32_t process_id) {
//     for (uint32_t i = 0; i < resource.size(); ++i) {
//         resource[i] -= need[i];
//         process_max[process_id][i] -= need[i];
//         process_alloca[process_id][i] += need[i];
//     }
//     unordered_map<int32_t, int32_t> finish;
//     for (const auto &i : process_max) {
//         finish[i.first] = false;
//     }
//     vector<int32_t> finish_count(process_max.size() + 1, 0);
//     for (uint32_t i = 0; i < process_max.size(); ++i) {
//         for (const auto &p_max : process_max) {
//             if (finish[p_max.first]) {
//                 continue;
//             }
//             int32_t can_finish = true;
//             for (uint32_t k = 0; k < p_max.second.size(); ++k) {
//                 if (resource[k] < p_max.second[k]) {
//                     can_finish = false;
//                     break;
//                 }
//             }
//             if (can_finish) {
//                 finish[p_max.first] = true;
//                 finish_count[i + 1] = finish_count[i] + 1;
//                 for (uint32_t k = 0; k < p_max.second.size(); ++k) {
//                     resource[k] += process_alloca[p_max.first][k];
//                 }
//                 break;
//             }
//         }
//         if (finish_count[i + 1] == finish_count[i]) {
//             return false;
//         }
//     }
//     for (const auto &i : finish) {
//         if (!i.second) {
//             return false;
//         }
//     }
//     return true;
// }