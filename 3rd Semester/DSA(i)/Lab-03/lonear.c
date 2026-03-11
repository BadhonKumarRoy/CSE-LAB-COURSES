#include<stdio.h>
int main(){

    int n,l,d;
    l=0;
    printf("Number of element: ");
    scanf("%d",&n);

    int arr[n];
    printf("Enter shorted elements: ");
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }

    printf("Enter searching element: ");
        scanf("%d",&d);

    for(int i=0; i<n; i++){
        if(arr[i]==d){
            l= i+1;
        }
    }
    if(l!=0){
        printf("Given data position at: %d ",l);
    }
    else{
        printf("data not found!");
    }
    return 0;

}

