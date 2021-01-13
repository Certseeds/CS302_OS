#include<stdio.h>

int main() {
    int x = 0;
    x += 1;
    x += 1;
    x += 1;
    printf("%d\n", x);
    return 0;
}
/*
  gcc -S opt.c -O0 -o opt0.s
    opt0.s
  gcc -S opt.c -O1 -o opt1.s
    opt1.s
  gcc -S opt.c -O2 -o opt2.s
    opt2.s
 */
