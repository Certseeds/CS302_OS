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
    TERMINATE,
    NONE
};
const vector<std::pair<string, COMMAND_TYPE>> command_name{
    std::pair<string, COMMAND_TYPE>("new", COMMAND_TYPE::NEW),
    std::pair<string, COMMAND_TYPE>("request", COMMAND_TYPE::REQUEST),
    std::pair<string, COMMAND_TYPE>("terminate", COMMAND_TYPE::TERMINATE)};

COMMAND_TYPE name_to_type(const string &str) {
    for (const auto &item : command_name) {
        if (str == item.first) {
            return item.second;
        }
    }
    return COMMAND_TYPE::NONE;  // should not reach there
}

class command {
   public:
    COMMAND_TYPE command_type;
    int32_t process_id;
    vector<int> resource;

    explicit command(int n) : command_type(COMMAND_TYPE::NONE), process_id(-1), resource(vector<int32_t>(n)){};

    command(COMMAND_TYPE ct, int32_t pi, vector<int> res) : command_type(ct), process_id(pi), resource(std::move(res)){};
};

class process {
public:
    int32_t process_id;
    vector<int> alloc_resource;
    vector<int> max_resource;
    vector<int> needed_resource;
    process(){};
    process(int32_t id, vector<int32_t> res, vector<int> max, vector<int> need) : process_id(id),
                                                                                  alloc_resource(std::move(res)),
                                                                                  max_resource(std::move(max)),
                                                                                  needed_resource(std::move(need)){};
    process(int32_t id, const vector<int> &max) {
        this->process_id = id;
        this->max_resource = vector<int32_t>(max);
        this->alloc_resource = vector<int32_t>(max.size(), 0);
        this->needed_resource = vector<int32_t>(max);
    };
};

#endif  //CS302_OS_REPORT_05_LAB08_SRC_BANKER_STRUCT_HPP
