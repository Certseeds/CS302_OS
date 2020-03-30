#include <stdio.h>
#include <stdlib.h>		// srand(), rand_r(), etc.
#include <unistd.h>		// sleep()
#include <time.h>		// time()
#include <pthread.h>		// pthread_*()

#define N		10	// size of the shared buffer
#define SLEEP_TIME	1
#define	SLEEP_CHANCE	4	// sleep for "SLEEP_TIME" seconds at a chance of "1 / SLEEP_CHANCE"
#define PRINT_BUF_SIZE	1024

#define IS_FULL(H, T, __SIZE)	((((T) + 1) % (__SIZE)) == (H))
#define IS_EMPTY(H, T, __SIZE)	((T) == (H))
#define NEXT_SLOT(X, __SIZE)	(((X) + 1) % (__SIZE))

#define PRODUCER_TURN	0
#define CONSUMER_TURN	1

/********************************\
 **                            **
 **  Global, Shared Variables  **
 **                            **
\********************************/

pthread_mutex_t	mutex	= PTHREAD_MUTEX_INITIALIZER;	// protect head, tail, and buffer
pthread_cond_t 	full	= PTHREAD_COND_INITIALIZER;	// the buffer is full
pthread_cond_t 	empty	= PTHREAD_COND_INITIALIZER;	// the buffer is empty

int head = 0, tail = 0;
int buffer[N];			// a shared ring buffer

/****************************\
 **                        **
 **   The drawing routine  **
 **                        **
\****************************/

void drawing(int turn, int item) {
	int last_produce = -1;
	int last_consume = -1;
	int i = 0, count;
	char print_buf[PRINT_BUF_SIZE];
	FILE *f = stdout;

	if(turn == PRODUCER_TURN) {
		last_produce = item;
		last_consume = -1;
	}

	if(turn == CONSUMER_TURN) {
		last_produce = -1;
		last_consume = item;
	}

/* format the output */

	print_buf[0] = '\0';

	// Consumer...

	if(last_consume == -1)
		sprintf(print_buf, "%s[ ]", print_buf);
	else
		sprintf(print_buf, "%s[%c]", print_buf, last_consume);

	sprintf(print_buf, "%s<---", print_buf);

	// The slots...

	count = 0;
	for(i = head; i != tail; i = (i+1)%N) {
		count++;
		sprintf(print_buf, "%s| %c ", print_buf, buffer[i]);
	}

	for(i = count; i < N-1; i++)
		sprintf(print_buf, "%s|   ", print_buf);
	sprintf(print_buf, "%s|", print_buf);

	// Producer...

	sprintf(print_buf, "%s<---", print_buf);
	if(last_produce == -1)
		sprintf(print_buf, "%s[ ]", print_buf);
	else
		sprintf(print_buf, "%s[%c]", print_buf, last_produce);

/* print the output */

	fprintf(f, "%s\n", print_buf);
	fflush(f);
}

/****************************\
 **                        **
 **  The producer routine  **
 **                        **
\****************************/

void *producer(void *nothing) {
	int item;
	unsigned int s;		// needed by thread-safe rand_r()

	while(1) {
		pthread_mutex_lock(&mutex);	// start of mutual exclusion.

			if(IS_FULL(head, tail, N))
				pthread_cond_wait(&full, &mutex);	// wait and unlock mutual exclusion.

			if(IS_EMPTY(head, tail, N))
				pthread_cond_signal(&empty);		// wake up the consumer.

			item = (rand_r(&s) % 26) + 'A';	// produce an item.
			buffer[tail] = item;		// insert an item.
			tail = NEXT_SLOT(tail, N);	// occupy one empty slot.
			drawing(PRODUCER_TURN, item);	// draw the change inside mutex.

		pthread_mutex_unlock(&mutex);	// end of mutual exclusion.

		if(rand_r(&s) % SLEEP_CHANCE == 0)
			sleep(1);
	}
}

/****************************\
 **                        **
 **  The consumer routine  **
 **                        **
\****************************/

void *consumer(void *nothing) {
	int item;
	unsigned int s;

	while(1) {
		pthread_mutex_lock(&mutex);	// start of mutual exclusion.

			if(IS_EMPTY(head, tail, N))
				pthread_cond_wait(&empty, &mutex);	// wait and unlock mutual exclusion.

			if(IS_FULL(head, tail, N))
				pthread_cond_signal(&full);		// wakeup the producer.

			item = buffer[head];		// consume an item.
			head = NEXT_SLOT(head, N);	// free one slot.
			drawing(CONSUMER_TURN, item);	// draw the change inside mutex.

		pthread_mutex_unlock(&mutex);	// end of mutual exclusion.

		if(rand_r(&s) % SLEEP_CHANCE == 0)
			sleep(1);
	}
}

/****************\
 **            **
 **  The main  **
 **            **
\****************/

int main(void) {
	pthread_t tid1, tid2;

	srand(time(NULL));
	pthread_create(&tid1, NULL, producer, NULL);	// create producer
	pthread_create(&tid2, NULL, consumer, NULL);	// create consumer

	// The join statements are just used for suspending the main threads.
	pthread_join(tid1, NULL);	// never reached.
	pthread_join(tid2, NULL);	// never reached.

	return 0;
}
