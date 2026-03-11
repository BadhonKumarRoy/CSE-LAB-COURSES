/*1. Write a C program to print all natural numbers
in reverse (from n to 1). - using loop*/
#include <stdio.h>

int main() {
    int n;
    printf("Enter a positive integer: ");
    scanf("%d", &n);
    printf("Natural numbers from %d to 1 are:\n", n);
    for (int i = n; i >= 1; i--) {
        printf("%d ", i);
    }

    return 0;
}
