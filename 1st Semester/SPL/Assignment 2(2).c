#include<stdio.h>
int main()
{
    float side1, side2, Area, Perimeter;
    printf("Please enter the length and breadth of the rectangle:");
    scanf("%f, %f", & side1, &side2);
    Area = side1 * side2;
    printf("Area = %.2f\n", Area);
    Perimeter = 2 * (side1 + side2);
    printf("Perimeter = %.2f", Perimeter);
    return 0;

}
