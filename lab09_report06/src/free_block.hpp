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
 * @Date: 2020-05-03 17:04:04 
 * @LastEditors  : nanoseeds
 */
#ifndef CS302_OS_LAB09_REPORT06_SRC_FREE_BLOCK_HPP
#define CS302_OS_LAB09_REPORT06_SRC_FREE_BLOCK_HPP

#include <cstdint>
#include <iostream>
#include <iomanip>

class free_block {    //空闲数据块
public:
    int32_t size;
    int32_t start_addr;
    free_block *next;


    explicit free_block() : size(0), start_addr(0), next(nullptr) {}

    explicit free_block(int32_t s, int32_t start_addr, free_block *f) :
            size(s), start_addr(start_addr), next(f) {}

    explicit free_block(const free_block &f) = delete;

    explicit free_block(free_block &&f) = delete;

    free_block &operator=(const free_block &f) = delete;

    free_block &operator=(free_block &&f) = delete;

    ~free_block() {
        this->start_addr = 0;
        this->size = 0;
        this->next = nullptr;
    }

    friend std::ostream &operator<<(std::ostream &output, free_block *fb_head) {
        free_block *fb = fb_head;
        output << std::string(21, '*') << "Free Memory" << std::string(21, '*') << std::endl;
        output << std::setw(20) << "start_addr" << std::setw(20) << "size" << std::endl;
        int cnt = 0;
        while (fb != nullptr) {
            cnt++;
            output << std::setw(20) << fb->start_addr << std::setw(20) << fb->size << std::endl;
            fb = fb->next;
        }
        if (cnt == 0) {
            output << "No Free Memory" << std::endl;
        } else {
            output << "Totally " << cnt << " free blocks" << std::endl;
        }
        return output;
    }
};

// 负责每次循环过后,将free_block中0 == size的去掉.
void clear_zero(free_block *free_block_head) {
    if (free_block_head == nullptr) {
        return;
    } else if (free_block_head->size == 0) {
        free_block *fb_head = free_block_head->next;
        delete free_block_head;
        free_block_head = fb_head;
        clear_zero(free_block_head);
        return;
    }
    free_block *fb_head = free_block_head;
    free_block *will_free;
    while (fb_head->next != nullptr) {
        if (fb_head->next->size == 0) {
            will_free = fb_head->next;
            fb_head->next = will_free->next;
            delete will_free;
        }
        fb_head = fb_head->next;
    }
}

void free_block_swap(free_block *fb1, free_block *fb2) {
    int32_t temp = fb1->size;
    fb1->size = fb2->size;
    fb2->size = temp;
    temp = fb1->start_addr;
    fb1->start_addr = fb2->start_addr;
    fb1->start_addr = temp;
}

#endif //CS302_OS_LAB09_REPORT06_SRC_FREE_BLOCK_HPP
