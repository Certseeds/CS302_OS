#include "stdio.h"
#include "unistd.h"

int main(){
    
    printf("return value of fork() is %d\n",fork());
    printf("mypid is %d, my parent pid is %d\n",getpid(),getppid());
    return 0;
}
