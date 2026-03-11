/*2. If a five-digit number is input through the keyboard, write a program to reverse the number.*/
#include<stdio.h>
int main()
{
    int number,a,b,c,d,e;
    printf("Enter a five digit number:");
    scanf("%d",&number);
    if (number < 10000 || number > 99999) {
        printf("The number must be a five-digit number.\n");}
    else {a=number%10;
     number=number/10;
     b=number%10;
     number=number/10;
     c=number%10;
     number=number/10;
     d=number%10;
     number=number/10;
     e=number%10;
     number=number/10;
     printf("Reversed number is:%d%d%d%d%d",a,b,c,d,e);}
    return 0;
}
