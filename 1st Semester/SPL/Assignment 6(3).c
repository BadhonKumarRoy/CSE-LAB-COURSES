/*6. In a town, the percentage of men is 52. The percentage of total literacy is 48.
If total percentage of literate men is 35 of the total population,
write a program to find the total number 48 Let Us C of illiterate men and women if the population of the town is 80,000.*/
#include<stdio.h>
int main()
{
    int population=80000;
    float pecentage_men=52;
    float percentage_literate=48;
    float percentage_literate_men=35;

    int number_of_men=(pecentage_men/100)*population;
    int number_of_women=population-number_of_men;

    int number_of_literate_men = (percentage_literate_men / 100) * population;
    int number_of_literate_people = (percentage_literate / 100) * population;

    int number_of_literate_women = number_of_literate_people - number_of_literate_men;

    int number_of_illiterate_men=number_of_men-number_of_literate_men;
    int number_of_illiterate_women=number_of_women-number_of_literate_women;
    printf("number of illiterate men: %d",number_of_illiterate_men);
    printf("\nnumber of illiterate women: %d",number_of_illiterate_women);


    return 0;
}
