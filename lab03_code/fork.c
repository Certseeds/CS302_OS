#include "stdio.h"
#include "unistd.h"

int main(){
    fork();
    printf("my pid is %d, my parent pid is %d.\n",getpid(),getppid());
}
