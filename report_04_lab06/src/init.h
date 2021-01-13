/*
 * @Github: https://github.com/Certseeds/CS302_OS
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2020-04-07 14:54:54
 * @LastEditors: nanoseeds
 * @LastEditTime: 2020-07-04 17:57:46
 */
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

// 拿到了50/50.
extern sem_t db, rc;
extern int readcount;