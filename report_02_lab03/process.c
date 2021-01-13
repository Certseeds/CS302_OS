/*
 * @Github: https://github.com/Certseeds
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2020-03-05 10:06:11
 * @LastEditors: nanoseeds
 * @LastEditTime: 2020-03-05 18:52:17
 */
#include <stdio.h>
#include <signal.h>
#include <stddef.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#include <sys/termios.h>

int main() {
    char *prog_argv[3];
    prog_argv[0] = "/usr/bin/vi";
    prog_argv[1] = "vi";
    prog_argv[2] = NULL;
    int cpid;/* 保存子进程的id号 */
    int ppid;/* 保存父进程的id号 */
    char buf[256];

    ppid = getpid();//得到近程号
    cpid = fork();
    signal(SIGTTOU, SIG_IGN);
    if (cpid < 0) {
        exit(-1);
    }
    if (!cpid) {
        cpid = getpid();
        fprintf(stdout, "ID(child)=%d\n", cpid);
        setpgid(cpid, cpid);
        tcsetpgrp(0, cpid);
        fprintf(stdout, "ID(child)=%d\n", getpid());
        execvp(prog_argv[0], prog_argv);
    } else {
        fprintf(stdout, "ID(parent)=%d\n", ppid);
        setpgid(cpid, cpid);/* 设置进程组 */
        tcsetpgrp(0, cpid);/* 设置控制终端为子进程拥有 */
        waitpid(cpid, NULL, 0);
        /* 父进程等待子进程执行完毕，所在进程组成为前台进程组 */
        tcsetpgrp(0, ppid);
    }
    while (1) {
        fprintf(stdout, "ID(parent)=%d\n", ppid);
        memset(buf, 0, 256);
        fgets(buf, 256, stdin);
        puts("ECHO: ");
        puts(buf);
        puts("\n");
    }

    return 0;
}
