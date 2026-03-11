#include<stdio.h>
int main()
{
    int value1 = 40;
    int value2 = 60;
    int value3 = 80;
    float average = (value1 + value2 + value3) / 3.0;
    printf("The average of %d, %d, and %d is %.2f\n", value1, value2, value3, average);
    return 0;
}
