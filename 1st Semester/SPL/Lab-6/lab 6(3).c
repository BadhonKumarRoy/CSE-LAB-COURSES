/*3. Write a C program to print sum of all even
numbers between 1 to n.*/
#include <stdio.h>
int main(){

    int n, sum=0;
    scanf("%d",&n);
    for(int i=1; i<=n; i++){
        if(i%2==0){
            sum+=i;
        }
    }
    printf("Sum = %d ",sum);

}
