/*7. Write a C program to find first and last digit
of any number.*/
#include <stdio.h>

int main() {
    int num, firstDigit, lastDigit;
    printf("Enter a number: ");
    scanf("%d", &num);

    lastDigit = num % 10;

    firstDigit = num;
    while (firstDigit >= 10) {
        firstDigit /= 10;
    }

    printf("First digit: %d\n", firstDigit);
    printf("Last digit: %d\n", lastDigit);

    return 0;
}

