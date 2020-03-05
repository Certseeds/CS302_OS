#include "stdio.h"
#include "unistd.h"
#include "sys/wait.h"
int main(){
    int pid=fork(); 
    if(pid){
        //printf("%d\n",pid);
        wait(NULL);
        //printf("%d\n",pid);
        printf("This is parent%d\n",getpid());
    }else{
        printf("This is child%d\n",getpid());
        printf("mypid is %d, my parent pid is %d\n",getpid(),getppid());
    }
    return 0;
}
