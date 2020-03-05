#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int main(){
    pid_t pid;
    pid = fork();
    if(!pid){
        execlp("/bin/ls","ls",NULL);
    }else{
        wait(NULL);
        printf("Oh my child!\n");
    }
    return 0;
}
