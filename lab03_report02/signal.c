/*
 * @Github: https://github.com/Certseeds
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2020-03-05 10:06:11
 * @LastEditors: nanoseeds
 * @LastEditTime: 2020-03-05 13:10:36
 */
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <stddef.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#include <sys/termios.h>

void ChildHandler (int sig, siginfo_t* sip, void* notused)/* 信号处理函数 */
{
	int status;
	printf("The process generating the signal is PID: %d\n",sip->si_pid);
	fflush(stdout);
	status=0;
	if(sip->si_pid==waitpid(sip->si_pid, &status, WNOHANG))/* WNOHANG 表示如果没有子进程退出，就不等待 */
	{
		if(WIFEXITED(status)||WTERMSIG(status))
			printf("The child is gone!!!!!\n");/* 子进程退出 */
		else
			printf("Uninteresting\n");/* alive */
	}else
	{
		printf("Uninteresting\n");
	}
};

int main()
{
	struct sigaction action;
	action.sa_sigaction=ChildHandler;/* 注册信号处理函数 */
	sigfillset(&action.sa_mask);// 64位置1,接受所有信号
	action.sa_flags = SA_SIGINFO;/* SA_SIGINFO表示允许向处理函数传递信息 */
	//SA_SIGINFO：信号处理函数是带有三个参数的sa_sigaction
	sigaction(SIGCHLD,&action,NULL);
  
	int pid;
	pid = fork();
	while(1)
	{
		if (pid)
			printf("PID(parent): %d\n",getpid());
		else
			printf("PID(child): %d\n",getpid());

		sleep(1);
	}
	
	return 0;
}  
