#include <stdio.h>

const int MAX = 1000000;

int main(void) {
    int i;
    for (i = 0; i < MAX / 5; i++)
        printf("x\nx\nx\nx\nx\n");
    return 0;

}