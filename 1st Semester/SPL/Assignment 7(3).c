/*7. If the total selling price of 15 items and the total profit earned on them is input through the keyboard,
write a program to find the cost price of one item.*/
#include<stdio.h>
 int main()
 {
     float a,b,c;
     float total_number_of_item=15;
     printf("Enter total selling price: ");
     scanf("%f",&a);
     printf("Enter total profit: ");
     scanf("%f",&b);
     c=(a-b)/total_number_of_item;
     printf("Total cost per item: %.2f",c);

     return 0;
 }

