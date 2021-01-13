/*
 * @Github: https://github.com/Certseeds/CS302_OS
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2020-08-04 11:07:33
 * @LastEditors: nanoseeds
 * @LastEditTime: 2020-08-04 15:28:51
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
 * @Date: 2020-08-03 22:31:08
 * @LastEditors  : nanoseeds
 */
#ifndef CS302_OS_REPORT_05_LAB08_SRC_BANKER_STRUCT_HPP
#define CS302_OS_REPORT_05_LAB08_SRC_BANKER_STRUCT_HPP

#include <string>
#include <vector>

using std::string;
using std::vector;
enum class COMMAND_TYPE {
    NEW,
    REQUEST,
    TERMINATE
};

std::vector<std::pair<string, COMMAND_TYPE>> get_command_name();

COMMAND_TYPE name_to_type(const string &str);

std::vector<std::pair<string, COMMAND_TYPE>> get_command_name() {
    static std::vector<std::pair<string, COMMAND_TYPE>> command_name{
            {"new",       COMMAND_TYPE::NEW},
            {"request",   COMMAND_TYPE::REQUEST},
            {"terminate", COMMAND_TYPE::TERMINATE}};
    return command_name;
}

COMMAND_TYPE name_to_type(const string &str) {
    for (const auto &item : get_command_name()) {
        if (str == item.first) {
            return item.second;
        }
    }
    return COMMAND_TYPE::TERMINATE;
    // should not reach there
}

class command {
public:
    COMMAND_TYPE command_type;
    int32_t process_id;
    vector<int32_t> resource;

    explicit command(int32_t n) : command_type(COMMAND_TYPE::NEW), process_id(-1), resource(vector<int32_t>(n)) {};

    command(COMMAND_TYPE ct, int32_t pi, int32_t r) : command(ct, pi, vector<int32_t>(r, 0)) {};

    command(COMMAND_TYPE ct, int32_t pi, vector<int32_t> res) : command_type(ct), process_id(pi),
                                                                resource(std::move(res)) {};
};

class process {
public:
    int32_t process_id{-1};
    vector<int32_t> alloc_resource;
    vector<int32_t> max_resource;
    vector<int32_t> needed_resource;

    process() = default;

    process(int32_t id, vector<int32_t> res, vector<int32_t> max, vector<int32_t> need) : process_id(id),
                                                                                          alloc_resource(
                                                                                                  std::move(res)),
                                                                                          max_resource(std::move(max)),
                                                                                          needed_resource(
                                                                                                  std::move(need)) {};

    process(int32_t id, const vector<int32_t> &max) : process(id,
                                                              vector<int32_t>(max.size(), 0),
                                                              vector<int32_t>(max),
                                                              vector<int32_t>(max)) {};
};

#endif  //CS302_OS_REPORT_05_LAB08_SRC_BANKER_STRUCT_HPP
