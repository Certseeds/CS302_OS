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
 * @Date: 2020-08-03 22:14:36 
 * @LastEditors  : nanoseeds
 */
#ifndef CS302_OS_INCLUDE_CS302_REDIRECT_H
#define CS302_OS_INCLUDE_CS302_REDIRECT_H

#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;

class CS302_redirect {
private:
    std::streambuf *strmin_buf;
    std::streambuf *strmout_buf;
    std::ifstream file_in = std::ifstream();
    std::ofstream file_out = std::ofstream();
public:
    // default path1 is input and path2 is output
    explicit CS302_redirect(const string &path1, const string &path2 = "") {
        this->strmin_buf = std::cin.rdbuf();
        this->strmout_buf = std::cout.rdbuf();
        this->file_in.open(path1);
        std::cin.rdbuf(file_in.rdbuf());
        if (!path2.empty()) {
            this->file_out.open(path2);
            std::cout.rdbuf(file_out.rdbuf());
        }
    }

    CS302_redirect(const CS302_redirect &redirect) = delete;

    CS302_redirect(CS302_redirect &&redirect) = delete;

    CS302_redirect &operator=(const CS302_redirect &redirect) = delete;

    CS302_redirect &operator=(CS302_redirect &&mat) = delete;

    ~CS302_redirect() {
        std::cout.rdbuf(strmout_buf);
        std::cin.rdbuf(strmin_buf);
        std::cout.flush();
    }

};

#endif //CS302_OS_INCLUDE_CS302_REDIRECT_H
