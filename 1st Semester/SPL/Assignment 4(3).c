 /*4. Two numbers are input through the keyboard into two locations C and D.
 Write a program to interchange the contents of C and D.*/
 #include<stdio.h>
 int main()
 {
     int c,d,e;
     printf("Enter the value of c: ",c);
     scanf("%d",&c);
     printf("Enter the value of d: ",d);
     scanf("%d",&d);
     e=c;
     c=d;
     d=e;
     printf("The value of c: %d\n",c);
     printf("The value of d: %d",d);
     return 0;
 }
