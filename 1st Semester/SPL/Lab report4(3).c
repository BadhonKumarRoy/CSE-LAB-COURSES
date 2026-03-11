/*3. Write a C program to take input of a character and identify the input symbol is alphabet or digit or other symbol*/
#include<stdio.h>
int main()
{
    char input;
    printf("Please enter an alphabet or a digit or a symbol: ");
    scanf("%c", &input);
    if (('A' <= input && input <= 'Z')||('a' <= input && input <= 'z'))
    {
        printf("The input is an Alphabet.");
    }
    else if ('0' <= input && input <= '9')
    {
        printf("The input is a Digit.");
    }
    else
    {
        printf("The input is a Symbol.");
    }
    return 0;
}
