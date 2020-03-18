#include <stdio.h>
#include <unistd.h>

int main(){
	int pid = fork();
	if (!pid){
		printf("I am child, my pid is %d\n", getpid());
		while (1){
			sleep(1);
		}
	}
	else{
		printf("I am parent, my pid is %d\n", getpid());
		while (1){
			sleep(1);
		}
	}
}

