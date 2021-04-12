/*dad_mem_mutex.c*/
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <ctime>
#include <sys/stat.h>
#include <unistd.h>
#include <pthread.h>

void * mom(void *pVoid) {
    int fd;
    printf("Mom comes home.\n");
    sleep(rand() % 2 + 1);
    printf("Mom checks the fridge.\n");
    fd = open("fridge", O_CREAT | O_RDWR | O_APPEND, 0777);
    if (lseek(fd, 0, SEEK_END) == 0) {
        printf("Mom goes to buy milk...\n");
        sleep(rand() % 2 + 1);
        printf("Mon comes back.\n");
        if (lseek(fd, 0, SEEK_END) > 0)
            printf("What a waste of food! The fridge can not hold so much milk!\n");
        else {
            write(fd, "milk", 4);
            printf("Mom puts milk in fridge and leaves.\n");
        }
    } else {
        printf("Mom closes the fridge and leaves.\n");
    }
    close(fd);
}

void * dad(void *pVoid) {
    int fd;
    printf("Dad comes home.\n");
    sleep(rand() % 2 + 1);
    printf("Dad checks the fridge.\n");
    fd = open("fridge", O_CREAT | O_RDWR | O_APPEND, 0777);
    if (lseek(fd, 0, SEEK_END) == 0) {
        printf("Dad goes to buy milk...\n");
        sleep(rand() % 2 + 1);
        printf("Dad comes back.\n");
        if (lseek(fd, 0, SEEK_END) > 0)
            printf("What a waste of food! The fridge can not hold so much milk!\n");
        else {
            write(fd, "milk", 4);
            printf("Dad puts milk in fridge and leaves.\n");
        }
    } else {
        printf("Dad closes the fridge and leaves.\n");
    }
    close(fd);
}

int main(int argc, char *argv[]) {
    srand(time(nullptr));
    pthread_t p1, p2;
    int fd = open("fridge", O_CREAT | O_RDWR | O_TRUNC, 0777);  //empty the fridge
    close(fd);
    // Create two threads (both run func)
    pthread_create(&p1, nullptr, mom, nullptr);
    pthread_create(&p2, nullptr, dad, nullptr);

    // Wait for the threads to end.
    pthread_join(p1, nullptr);
    pthread_join(p2, nullptr);
}
