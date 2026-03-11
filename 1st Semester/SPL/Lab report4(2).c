/*2. Write a C program to take input of a number and the number is positive, negative, or zero and the number is odd or even.*/
#include<stdio.h>
int main()
{
    int num;
    printf("Please enter an integer: ");
    scanf("%d", &num);
    if (num > 0)
    {
        printf("The number is positive.\n");
    }
    else if (num < 0)
    {
        printf("The number is negative.\n");
    }
    else
    {
        printf("And the number is zero.\n");
    }
    if (num %2 == 0)
    {
        printf("And the number is even.\n");
    }
    else if (num == 0)
    {
        printf("And the number is neither even or odd.\n");
    }
    else
    {
        printf("And the number is odd.");
    }
    return 0;
}
