/*  CS302_OS
    Copyright (C) 2020 certseeds

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
/*
 * @Github: https://github.com/Certseeds/CS302_OS
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2020-04-07 14:54:54
 * @LastEditors: nanoseeds
 * @LastEditTime: 2020-04-08 01:38:17
 */
#include "init.h"

void *reader(int *buffer) {
    // Reader should read the value of buffer
    // Reader cannot start to work when there is any writer working
    // You should implement this using semaphore
    sem_wait(&rc);
    if (0 == readcount) {
        sem_wait(&db);
    }
    // You should output this just after this thread gets semaphore
    printf("Reader gets sem\n");
    readcount++;
    sem_post(&rc);
    // you should output this just before this thread releases the semaphore
    printf("Reader reads %d and releases\n", *buffer);
    sem_wait(&rc);
    readcount--;
    if (0 == readcount) {
        sem_post(&db);
    }
    sem_post(&rc);
}

// If no reader and writer, then new reader can read.
// If writer is waiting and other readers are reading, then new reader can read.
// If writer is writing, then new reader waits.