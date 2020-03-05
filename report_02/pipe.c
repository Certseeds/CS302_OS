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


int main(int argc, char *argv[])
{
	int status;
	int pid[2];//���̺�
	int pipe_fd[2];//pipe����������һ��pipe���������������ֱ�����readʱ������룬��writeʱ������
  
	char *prog1_argv[4];//�������̵�ʱ��Ĳ���
	char *prog2_argv[2];

	char rwBuffer[1024] = {'\0'};//��read��write��дpipeʱ��ʹ�õĻ�����
  
	prog1_argv[0]="/bin/ls";/* ����ls�Ĳ����� */
	prog1_argv[1]="-l";
	prog1_argv[2]="/etc/";
	prog1_argv[3]=NULL;
  
	prog2_argv[0]="/bin/more";/* ����more�Ĳ����� */
	prog2_argv[1]=NULL;

	if (pipe(pipe_fd)<0)//����pipe�������������������������
	{  
		perror("pipe failed");
		exit(errno);
	}

	if ((pid[0]=fork())<0)/* ������Ϊls������ӽ��� */
	{
		perror("Fork failed");
		exit(errno);
	}

	if (!pid[0])/* ls�ӽ��� */
	{
		read(pipe_fd[0],rwBuffer,1024);//�ȹܵ������������ȴ������̷�������
		fprintf(stdout,"\n\n-----------------------%s|rec---------------------------\n\n",rwBuffer);

		/*����Ҫ�ٶ�ȡ��,�رն���*/
		close(pipe_fd[0]);
		dup2(pipe_fd[1],1);/*���ܵ���д���������Ƹ���׼���,Ȼ��ر�*/
		close(pipe_fd[1]);
		execvp(prog1_argv[0], prog1_argv);//����ls
	}
  
	if (pid[0])/*�����̣�Ϊmore�����ӽ���*/
	{
		if ((pid[1]=fork())<0)//�ٴδ�������
		{
			perror("Fork failed");
			exit(errno);
		}
		if (!pid[1])//�ӽ���
		{
			close(pipe_fd[1]);
			dup2(pipe_fd[0],0);/*���ܵ��Ķ����������Ƹ���׼���룬Ȼ��ر�*/
			close(pipe_fd[0]);
			execvp(prog2_argv[0],prog2_argv);
		}else{
			fprintf(stdout,"\n\n-------------------------%s|send---------------------\n\n",rwBuffer);
			sprintf(rwBuffer,"start1");
			write(pipe_fd[1],rwBuffer,strlen(rwBuffer));//������д�뵽�ܵ�
			fprintf(stdout,"\n\n-------------------------%s|send---------------------\n\n",rwBuffer);
			sprintf(rwBuffer,"start2");
			write(pipe_fd[1],rwBuffer,strlen(rwBuffer));//������д�뵽�ܵ�
		}

		close(pipe_fd[0]);
		close(pipe_fd[1]);
		waitpid(pid[1],&status,0);
		printf("Done waiting for more.\n");
	}

	return 0;
}
