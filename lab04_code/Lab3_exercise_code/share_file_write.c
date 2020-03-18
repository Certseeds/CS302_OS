#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

char buff[1000];

int main(){
	int fd = open("ww", O_WRONLY, 0666);
	int pid = fork();
	if (!pid){
		int i;
		for (i = 0; i < 1000; i++){
			buff[i] = 'w';
		}
		write(fd, buff, strlen(buff));
	}
	else{
		int i;
		for (i = 0; i < 1000; i++){
			buff[i] = 'y';
		}
		write(fd, buff, strlen(buff));
	}
	return 0;
}
		
