/*6. Write a C program to enter any number and
calculate sum of all natural numbers  between
1 to n.*/
#include <stdio.h>

int main() {
    int n,sum=0;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {

        sum+=i;
    }
    printf("Sum = %d",sum);

    return 0;
}
