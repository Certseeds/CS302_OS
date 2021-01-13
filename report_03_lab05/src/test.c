/*
 * @Github: https://github.com/Certseeds/CS302_OS
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2020-03-30 11:19:18
 * @LastEditors: nanoseeds
 * @LastEditTime: 2020-04-01 00:52:31
 */
/* CS302_OS
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
 * @Date: 2020-03-30 11:19:18
 * @LastEditors  : nanoseeds
 */
#include <stdio.h>

#ifdef __GNUC__

#include <unistd.h>

#define sleepTime 1
#else
#include<windows.h>
#define sleepTime 1000
#endif

int main() {
    int x = 114514;
    printf("%d", x);
    for (int i = 0; i < 5000; i++) {
        printf("%d \n", x);
        sleep(1);
        printf("%d \n", x);
        fflush(stdout);
    }
    printf("%d\n", x);
    return 0;
}