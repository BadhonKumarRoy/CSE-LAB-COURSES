#include<stdio.h>
int main()
{
    float number1, number2, number3, summation, subtraction, multiplication, division;
    printf("Please enter the value of number1:");
    scanf("%f", &number1);
    printf("Please enter the value of mumber2:");
    scanf("%f", &number2);
    printf("Please enter the value of number3:");
    scanf("%f", &number3);
    summation = number1 + number2 + number3;
    subtraction = number1 - number2 - number3;
    multiplication = number1 * number2 * number3;
    division = number1 / number2 / number3;
    printf("Summation = %.2f\n", summation);
    printf("subtraction = %.2f\n", subtraction);
    printf("multiplication = %.2f\n", multiplication);
    printf("division = %.2f\n", division);
    return 0;

}
