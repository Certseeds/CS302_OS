#include <stdio.h>
#include <unistd.h>
#include <string.h>

char buff[1000];

int main(){
	FILE* fp = fopen("ww", "w");
	int pid = fork();
	if (!pid){
		int i;
		for (i = 0; i < 1000; i++){
			buff[i] = 'w';
		}
		fwrite(buff, strlen(buff), 1, fp);
	}
	else{
		int i;
		for (i = 0; i < 1000; i++){
			buff[i] = 'y';
		}
		fwrite(buff, strlen(buff), 1, fp);
	}
	return 0;
}
		
