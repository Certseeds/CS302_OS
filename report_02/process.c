#include <stdio.h>
#include <signal.h>
#include <stddef.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#include <sys/termios.h>

int main()
{ 
	char *prog_argv[3];
	prog_argv[0]="/usr/bin/vi";
	prog_argv[1]="vi";
	prog_argv[2]=NULL;
	int cpid;/* �����ӽ��̵�id�� */
	int ppid;/* ���游���̵�id�� */
	char buf[256];
  
	ppid=getpid();//�õ����̺�
	cpid=fork();
  
	if (cpid<0){
		exit(-1);
	}
	if (!cpid){
		cpid=getpid();
		fprintf(stdout,"ID(child)=%d\n",cpid);
		//setpgid(cpid,cpid);
		tcsetpgrp(0,cpid);
		fprintf(stdout,"ID(child)=%d\n",getpid());
		execvp(prog_argv[0],prog_argv);
	}else{
	    fprintf(stdout,"ID(parent)=%d\n",ppid);
	    fprintf(stdout,"ID(parent)=%d\n",ppid);
	    fprintf(stdout,"ID(parent)=%d\n",ppid);
	    fprintf(stdout,"ID(parent)=%d\n",ppid);
		setpgid(cpid,cpid);/* ���ý����� */
	    tcsetpgrp(0,cpid);/* ���ÿ����ն�Ϊ�ӽ���ӵ�� */
	    waitpid(cpid,NULL,0);
	    /* �����̵ȴ��ӽ���ִ����ϣ����ڽ������Ϊǰ̨������ */
	    tcsetpgrp(0,ppid);
	}
	while(1){
	    fprintf(stdout,"ID(parent)=%d\n",ppid);
		memset(buf, 0, 256);
		fgets(buf, 256, stdin);
		puts("ECHO: ");
		puts(buf);
		puts("\n");
	}

	return 0;
}
