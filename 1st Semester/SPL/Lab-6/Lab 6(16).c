/*16. Write a c program to find out the sum of series
1 + 2 + …. + n.*/
#include <stdio.h>

int main() {
    int n, sum;

    printf("Enter a positive integer: ");
    scanf("%d", &n);

    sum = n * (n + 1) / 2;

    printf("Sum of the series 1 + 2 + ... + %d is: %d\n", n, sum);

    return 0;
}

