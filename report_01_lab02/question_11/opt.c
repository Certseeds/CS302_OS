/*
 * @Github: https://github.com/Certseeds
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2020-02-19 18:35:23
 * @LastEditors: nanoseeds
 * @LastEditTime: 2020-02-29 21:20:02
 */

#include<stdio.h>

int main() {
    int x = 114514;
    x += 1;
    x += 1;
    x += 1;
    printf("%d\n", x);
    return 0;
}
// it is really useful to use
//  gcc -S -fverbose-asm -g opt.c -O0  -o opt0_3.s