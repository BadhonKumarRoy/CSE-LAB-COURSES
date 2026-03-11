/*20. Write a c program to find out the sum of series
1^2 + 2^2 + …. + n^2.*/
#include <stdio.h>

int main() {
    int n, sum = 0;
    printf("Enter a positive integer n: ");
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        sum += i * i;
    }
    printf("Sum of the series 1^2 + 2^2 + ... + %d^2 is: %d\n", n, sum);

    return 0;
}

