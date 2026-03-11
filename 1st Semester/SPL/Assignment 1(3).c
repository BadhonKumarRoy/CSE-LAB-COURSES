/*1. The distance between two cities (in kilometers) is input through the keyboard.
Write a program to convert and print this distance in meters, feet, inches and centimeters.*/
#include<stdio.h>
int main()
{
    float a, b, c, d, e;
    printf("Please enter the Distance in km: ");
    scanf("%f",&a);
    b=a*1000;
    c=a*3280.84;
    d=a*39370.1;
    e=a*100000;
    printf("%.2f km is equal to %.2f m\n", a,b);
    printf("%.2f km is equal to %.2f feet\n", a,c);
    printf("%.2f km is equal to %.2f inches\n", a,d);
    printf("%.2f km is equal to %.2f cm\n", a,e);
    return 0;
}
