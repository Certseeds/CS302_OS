/**
 * @Github: https://github.com/Certseeds/CS302_DSAA_template
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2020-07-15 21:42:36 
 * @LastEditors: nanoseeds
 * @LICENSE: MIT
 */
/*
MIT License

CS302_DSAA_template 

Copyright (C) 2020 nanoseeds

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#ifndef CS302_OS_INCLUDE_CS302_TIMER_H
#define CS302_OS_INCLUDE_CS302_TIMER_H

#include <iostream>
#include <chrono>

std::chrono::milliseconds get_ms() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch());
}

class CS302_timer {
private:
    std::chrono::milliseconds ms{};
public:
    explicit CS302_timer() noexcept {
        std::cout << "complier in " << __DATE__ << " " << __TIME__ << std::endl;
        ms = get_ms();
    }

    CS302_timer(const CS302_timer &timer) = delete;

    CS302_timer(CS302_timer &&timer) = delete;

    CS302_timer &operator=(const CS302_timer &timer) = delete;

    CS302_timer &operator=(CS302_timer &&mat) = delete;

    ~CS302_timer() {
        std::cout << "cost " << get_ms().count() - ms.count() << " ms\n";
    }

};

#endif //CS302_OS_INCLUDE_CS302_TIMER_H
