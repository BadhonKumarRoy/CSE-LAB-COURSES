/*5. If a four-digit number is input through the keyboard.
Write a program to obtain the sum of the first and last digit of the number*/
#include<stdio.h>
int main()
{
    int num,sum,a,b,c,d;
    printf("Enter a four-digit number: ");
    scanf("%d",&num);
    if(num <1000 || num>9999){
        printf("Must enter a four-digit number.");}
    else{a=num %10;
     num=num/10;
     b=num %10;
     num=num/10;
     c=num %10;
     num=num/10;
     d=num %10;
     num=num/10;
    sum=a+d;
    printf("Sum of the first and last digit of this number is: %d",sum);}
    return 0;
}
