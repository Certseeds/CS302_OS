#include<stdio.h>

void show_msg();

int main() {
    show_msg();
    return 0;
}

void show_msg() {
    printf("hello OS\n");
    return;
}

/*
 gcc hello.c
   a.out
 gcc -c hello.c
   hello.o
 gcc -E hello.c
   output a lot.
 gcc -S hello.c
   hello.s
 gcc -o hello hello.c
   hello
 */