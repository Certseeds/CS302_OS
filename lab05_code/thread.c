#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS	5

struct msg{
  int id;
  char* word; 
};

void PrintHello(struct msg* arg)
{
  printf("%s%d!\n", arg->word, arg->id);
  arg->id=1000;
  pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
  pthread_t threads[NUM_THREADS];
  struct msg arg[NUM_THREADS];
  char* word = "Hello World! It's me, thread #";
  for(int t=0;t<NUM_THREADS;t++){
    printf("In main: creating thread %d\n", t);
    arg[t] = (struct msg){t, word};
    pthread_create(&threads[t], NULL, &PrintHello, &arg[t]);
  }
  for(int t=0;t<NUM_THREADS;t++)
    pthread_join(threads[t], NULL);
  printf("\nall threads finish.\n");
  /* Last thing that main() should do */
  pthread_exit(NULL);
}