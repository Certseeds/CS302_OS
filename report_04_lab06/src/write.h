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
 * @LastEditTime: 2020-04-08 01:38:31
 */
#include "init.h"

void *writer(int *buffer) {
    // Writer should change buffer to buffer+1
    //(e.g., before *buffer==0,  after *buffer==1)
    // Writer cannot start to work when there is any reader or writer
    // working You should implement this using semaphore
    sem_wait(&db);
    // sem_wait(&rc);
    // You should output this just after this thread gets semaphore
    printf("writer gets sem\n");
    // int rc_value = 0;
    // do {
    //     sem_getvalue(&rc, &rc_value);
    // } while (rc_value != 1);
    (*buffer)++;
    // you should output this just before this thread releases the semaphore
    printf("writer writes %d and releases\n", *buffer);
    sem_post(&db);
    // sem_post(&rc);
}
// When new writer coming,
// If no reader, then new writer can write.
// If reader is reading, then new writer waits.
// If writer is writing, then new writer waits.
