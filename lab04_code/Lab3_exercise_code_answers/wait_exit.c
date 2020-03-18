#include <stdio.h>
#include <unistd.h>

int main(){
	int pid;
	if ((pid = fork()) != 0){
		printf("Look at the status of the child process %d\n", pid);
		while (getchar() != '\n');
		wait(NULL);
		printf("Look again!\n");
		while (getchar() != '\n');
	}
	return 0;
}


