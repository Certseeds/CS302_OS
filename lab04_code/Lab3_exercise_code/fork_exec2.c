#include <unistd.h>
#include <stdio.h>

int system_ver_CS302(const char *cmd_str){
	if(cmd_str == -1)
		return -1;
	if(fork() == 0) {
		execl(cmd_str,cmd_str, NULL);
		fprintf(stderr, "%s:command not found\n",cmd_str);
		exit(-1);
	}
	wait(NULL);
	return 0;
}

int main(void){
	printf("before...\n\n");
	system_ver_CS302("/bin/ls");
	printf("\nafter...\n");
	return 0;
}