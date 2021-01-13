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
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <time.h>
#include <stdbool.h>

/**
 * @Github: https://github.com/Certseeds/CS302_OS
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2020-03-30 18:06:51
 * @LastEditors  : nanoseeds
 */
//void sig_handler(int sig, siginfo_t *info, void *notused);
//int main();
//int main(){
//    struct timeval interval;
//    struct itimerval new, old;
//    struct sigaction newact, oldact1, oldact2;
//
//    interval.tv_sec = 1;
//    interval.tv_usec = 0;
//    // 100 ms = 10^-1s = 10^-1 * 10^6 us = 10^5 us.
//    newact.sa_sigaction = sig_handler; //
//    sigaction(SIGCHLD, &newact, &oldact1); // 对原来SIGCHLD信号的处理,去了oldact1
//    sigaction(SIGVTALRM, &newact, &oldact2);// 对原来SIGVTALRM信号的处理,去了oldact2
//    sigemptyset(&newact.sa_mask); // make newact empty.
//    newact.sa_flags = SA_SIGINFO; // set it for make sa_sigaction can be use
//    new.it_interval = interval;
//    new.it_value = interval;
//    setitimer(ITIMER_VIRTUAL, &new, &old); // generate SIGVTALRM every 100ms.
//    while(1);
//    return 0;
//}
//void sig_handler(int sig, siginfo_t *info, void *notused) {
//    int status;
//    int ret;
//    printf("sig recive is %d: \n",sig);
//
//    fflush(stdout);
//}
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdint.h>

void sigroutine(int signo) {
    printf("signo is %d : ", signo);
    switch (signo) {
        case SIGALRM: {
            printf("Catch a signal -- SIGALRM \n");
            break;
        }
        case SIGVTALRM: {
            printf("Catch a signal -- SIGVTALRM\n");
            break;
        }
    }
    fflush(stdout);
}

int main(int argc, char **argv) {
    struct itimerval value, ovalue, value2, value3;
    printf("process id is %dn", getpid());
    signal(SIGALRM, sigroutine);    //为SIGALRM信号绑定sigroutine函数
    signal(SIGVTALRM, sigroutine);  //为SIGVTALRM信号绑定sigroutine函数
    value.it_value.tv_sec = 1;//设定起始时间
    value.it_value.tv_usec = 0;
    value.it_interval.tv_sec = 1;//设定终止时间
    value.it_interval.tv_usec = 0;
    setitimer(ITIMER_VIRTUAL, &value, &ovalue);
    value2.it_value.tv_sec = 2;
    value2.it_value.tv_usec = 0;
    value2.it_interval.tv_sec = 2;
    value2.it_interval.tv_usec = 0;
    setitimer(ITIMER_REAL, &value2, &value3);
    int x = 1;
    for (;;) {
        x = x + 1;
        if (x == INT32_MAX / 2) {
            printf("114514");
            x = 1;
        }
    }
}