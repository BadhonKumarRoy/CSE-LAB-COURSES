#include<stdio.h>
int main()
{
    //finding area of the equilateral triangle
    float side, area;
    printf("Please enter length of any side of the equilateral triangle:");
    scanf("%f", &side);
    area = (sqrt(3)/4) * (side * side);
    printf("The area of the equilateral triangle is: %.2f\n", area);
    return 0;
}
