/*
 * @Github: https://github.com/Certseeds
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2020-03-05 10:06:11
 * @LastEditors: nanoseeds
 * @LastEditTime: 2020-03-05 11:24:10
 */
#include <string.h>
#include <stdio.h>
#include <errno.h>


int main(int argc, char *argv[]) {
    int status;
    int pid[2];//进程号
    int pipe_fd[2];//pipe的描述符，一个pipe有两个描述符，分别用于read时候的输入，和write时候的输出

    char *prog1_argv[4];//启动进程的时候的参数
    char *prog2_argv[2];

    char rwBuffer[1024] = {'\0'};//用read和write读写pipe时候使用的缓冲区

    prog1_argv[0] = "/bin/ls";/* 命令ls的参数表 */
    prog1_argv[1] = "-l";
    prog1_argv[2] = "/etc/";
    prog1_argv[3] = NULL;

    prog2_argv[0] = "/bin/more";/* 命令more的参数表 */
    prog2_argv[1] = NULL;

    if (pipe(pipe_fd) < 0)//创建pipe，获得用于输入和输出的描述符
    {
        perror("pipe failed");
        exit(errno);
    }

    if ((pid[0] = fork()) < 0)/* 父进程为ls命令创建子进程 */
    {
        perror("Fork failed");
        exit(errno);
    }

    if (!pid[0])/* ls子进程 */
    {
        read(pipe_fd[0], rwBuffer, 1024);//度管道，会阻塞，等待父进程发布命令
        fprintf(stdout, "\n\n-----------------------%s|rec---------------------------\n\n", rwBuffer);

        /*不需要再读取了,关闭读端*/
        close(pipe_fd[0]);
        dup2(pipe_fd[1], 1);/*将管道的写描述符复制给标准输出,然后关闭*/
        close(pipe_fd[1]);
        execvp(prog1_argv[0], prog1_argv);//调用ls
    }

    if (pid[0])/*父进程，为more创建子进程*/
    {
        if ((pid[1] = fork()) < 0)//再次创建进程
        {
            perror("Fork failed");
            exit(errno);
        }
        if (!pid[1])//子进程
        {
            close(pipe_fd[1]);
            dup2(pipe_fd[0], 0);/*将管道的读描述符复制给标准输入，然后关闭*/
            close(pipe_fd[0]);
            execvp(prog2_argv[0], prog2_argv);
        } else {
            fprintf(stdout, "\n\n-------------------------%s|send---------------------\n\n", rwBuffer);
            sprintf(rwBuffer, "start1");
            write(pipe_fd[1], rwBuffer, strlen(rwBuffer));//将命令写入到管道
            fprintf(stdout, "\n\n-------------------------%s|send---------------------\n\n", rwBuffer);
            sprintf(rwBuffer, "start2");
            write(pipe_fd[1], rwBuffer, strlen(rwBuffer));//将命令写入到管道
        }

        close(pipe_fd[0]);
        close(pipe_fd[1]);
        waitpid(pid[1], &status, 0);
        printf("Done waiting for more.\n");
    }

    return 0;
}
