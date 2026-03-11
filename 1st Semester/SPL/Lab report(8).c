/*8.  Write a C program to input marks of five subjects Physics, Chemistry, Biology, Mathematics and Computer.
 Calculate percentage and grade according to following:
Percentage >= 90%: Grade A
Percentage >= 80%: Grade B
Percentage >= 70%: Grade C
Percentage >= 60%: Grade D
Percentage >= 40%: Grade E
Percentage < 40%: Grade F   */
#include<stdio.h>
int main()
{

    float physics,chemistry,biology,mathematics,computer,percentage;
    printf("Enter the marks of physics:");
    scanf("%f",&physics);
    printf("Enter the marks of chemistry:");
    scanf("%f",&chemistry);
    printf("Enter the marks of biology:");
    scanf("%f",&biology);
    printf("Enter the marks of mathematics:");
    scanf("%f",&mathematics);
    printf("Enter the marks of computer:");
    scanf("%f",&computer);
    if (physics < 0 || physics > 100 || chemistry < 0 || chemistry > 100 ||
        biology < 0 || biology > 100 || mathematics < 0 || mathematics > 100 ||
        computer < 0 || computer > 100) {
        printf("Invalid input! Marks should be between 0 and 100.\n");
        }
    percentage =((physics+chemistry+biology+mathematics+computer+percentage)/500)*100;
    printf("Percentage:%f",percentage);
    if (percentage >= 90){
        printf("\nGrade:A");
    }
    else if (percentage >= 80){
        printf("\nGrade:B");
    }
    else if (percentage >= 70){
        printf("\nGrade:C");
    }
    else if (percentage >= 60){
        printf("\nGrade:D");
    }
    else if (percentage >= 40){
        printf("\nGrade:E");
    }
    else if (percentage < 40){
        printf("\nGrade:F");
    }
    return 0;
}
