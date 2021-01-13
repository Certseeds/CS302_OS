#include<stdio.h>
#include<math.h>

// gcc -o sqrt sqrt.c -lm
int main() {
    int x = 0;
    int y = 0;
    double res = 0;
    scanf("%d%d", &x, &y);
    res = sqrt(pow(x, 2) + pow(y, 2));
    printf("%f\n", res);
    return 0;
}