/*3. If a five-digit number is input through the keyboard, write a program to calculate the sum of each digits.*/
#include<stdio.h>
int main()
{
    int num,sum,a,b,c,d,e;
    printf("Enter a five digit number:");
    scanf("%d",&num);
    if (num<10000||num>99999) {
        printf("The number must be a five-digit number.\n");}

    else {a=num%10;
     num=num/10;
     b=num%10;
     num=num/10;
     c=num%10;
     num=num/10;
     d=num%10;
     num=num/10;
     e=num%10;
     num=num/10;
     sum=a+b+c+d+e;
     printf("Sum of five digit is:%d",sum);}
    return 0;
}
