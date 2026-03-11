/*19. Write a c program to find out the sum of series
1 + (1+ 2) + (1+2+3) …. + (1 + 2 + 3 + ………… + n).*/
#include <stdio.h>

int main() {
    int n, sum = 0;

    printf("Enter a positive integer n: ");
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {

        sum += (i * (i + 1)) / 2;
    }

    printf("Sum of the series 1 + (1+2) + (1+2+3) + ... + (1+2+3+...+%d) is: %d\n", n, sum);

    return 0;
}

