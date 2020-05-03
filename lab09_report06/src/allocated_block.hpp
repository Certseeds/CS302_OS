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
 * @Date: 2020-05-03 17:40:53 
 * @LastEditors  : nanoseeds
 */
#ifndef CS302_OS_LAB09_REPORT06_SRC_ALLOCATED_BLOCK_HPP
#define CS302_OS_LAB09_REPORT06_SRC_ALLOCATED_BLOCK_HPP

#include <cstdint>
#include <iostream>

class allocated_block {    //空闲数据块
public:
    int32_t pid;
    int32_t size;
    int32_t start_addr;
    allocated_block *next;


    explicit allocated_block() : pid(0), size(0), start_addr(0), next(nullptr) {};

    explicit allocated_block(int32_t p, int32_t s, int32_t sa, allocated_block *f) :
            pid(p), size(s), start_addr(sa), next(f) {}

    explicit allocated_block(const allocated_block &f) = delete;

    explicit allocated_block(allocated_block &&f) = delete;

    allocated_block &operator=(const allocated_block &f) = delete;

    allocated_block &operator=(allocated_block &&f) = delete;

    ~allocated_block() {
        this->pid = 0;
        this->start_addr = 0;
        this->size = 0;
        this->next = nullptr;
    }


    int32_t allocate_mem_FF_BF(
            free_block *freeBlock_head,
            int32_t min_slice) {
        free_block *fb = new free_block(0, 0, freeBlock_head);
        free_block *fb_head = fb;
        int will_return = -1;
        while (fb->next != nullptr) {
            if (fb->next->size >= this->size) {
                will_return = fb->next->start_addr;
                if (fb->next->size <= this->size + min_slice) {
                    this->size = fb->next->size;
                    fb->next->size = 0;
                    fb->next->start_addr = 0;
                } else {
                    fb->next->size -= this->size;
                    fb->next->start_addr += this->size;
                }
                break;
            }
            fb = fb->next;
        }
        delete fb_head;
        return will_return;
    }

    int allocate_mem_WF(free_block *freeBlock_head,
                        int32_t min_slice) {
        int will_return = -1;
        if (freeBlock_head->size >= this->size) {
            will_return = freeBlock_head->start_addr;
            if (freeBlock_head->size <= this->size + min_slice) {
                this->size = freeBlock_head->size;
                freeBlock_head->size = 0;
                freeBlock_head->start_addr = 0;
            } else {
                freeBlock_head->size -= this->size;
                freeBlock_head->start_addr += this->size;
            }
        }
        return will_return;
    }

    friend std::ostream &operator<<(std::ostream &output, allocated_block *ab_head) {
        allocated_block *ab = ab_head;
        output << std::string(19, '*') << "Used Memory" << std::string(21, '*') << std::endl;
        output <<
               std::setw(10) << "PID " <<
               std::setw(10) << "start_addr " <<
               std::setw(20) << "size " <<
               std::endl;
        int32_t cnt = 0;
        while (ab != nullptr) {
            cnt++;
            output <<
                   std::setw(10) << ab->pid << " " <<
                   std::setw(10) << ab->start_addr << " " <<
                   std::setw(20) << ab->size << " " <<
                   std::endl;
            ab = ab->next;
        }
        if (cnt == 0) {
            output << "No allocated block" << std::endl;
        } else {
            output << "Totally " << cnt << " allocated blocks" << std::endl;
        }
        return output;
    }

};

#endif //CS302_OS_LAB09_REPORT06_SRC_ALLOCATED_BLOCK_HPP
