/*6. Write a C program to check whether a character is uppercase or lowercase alphabet.*/
#include<stdio.h>
int main()
{
    char ch;
    printf("Please enter an Alphabet: ");
    scanf("%c", &ch);
    if ('A'<=ch && ch<='Z')
    {
        printf("The Alphabet is in uppercase.");
    }
    else if ('a'<=ch && ch<='z')
    {
        printf("The Alphabet is in lowercase.");
    }
    else
    {
        printf("The input is not an Alphabet.");
    }
    return 0;
}
