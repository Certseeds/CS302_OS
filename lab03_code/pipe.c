/*
 * @Github: https://github.com/Certseeds
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2020-03-04 16:22:18
 * @LastEditors: nanoseeds
 * @LastEditTime: 2020-03-05 09:38:03
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>

int pid;
int pipe_fd[2];
char buff[1024], input[1024];

void write_data() {
    sleep(1);
    printf("\nMy pid is %d\n", getpid());
    printf("please input a string:\n");
    scanf("%s", input);
    write(pipe_fd[1], input, strlen(input));
    printf("Write finished\n");
    kill(getppid(), SIGALRM);
}

void finish_write() {
    close(pipe_fd[1]);
    printf("%d finish write\n", getpid());
    exit(0);
}

void read_data() {
    sleep(1);
    printf("\nMy pid is %d\n", getpid());
    printf("read begins\n");
    memset(buff, 0, sizeof(buff));
    read(pipe_fd[0], buff, 1024);
    printf("Read finished\n");
    printf("Message is: %s\n", buff);
    kill(pid, SIGALRM);
}

void finish_read() {
    close(pipe_fd[0]);
    printf("%d finish read\n", getpid());
    exit(0);
}

int main() {
    if (pipe(pipe_fd) < 0) {
        printf("pipe create failed\n");
    }

    if ((pid = fork()) < 0) {
        printf("fork failed\n");

    }

    if (!pid) {
        printf("child process begins,pid=%d\n", getpid());
        signal(SIGALRM, write_data);
        signal(SIGINT, finish_write);
        kill(getpid(), SIGALRM);
        while (1) {
        }

    } else {
        printf("parent process begins, pid=%d\n", getpid());
        signal(SIGALRM, read_data);
        signal(SIGINT, finish_read);
        while (1) {
        }
    }
}


