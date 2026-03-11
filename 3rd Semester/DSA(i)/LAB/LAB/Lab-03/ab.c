#include<stdio.h>
int main()
{
    int n,l=0,r;
    int d,m;
    printf("Enter the number of elements: ");
    scanf("%d",&n);

    int a[25];
    printf("Enter the elements: ");
    for(int i=0; i<n; i++){
        scanf("%d",&a[i]);
    }
    printf("Enter the data to find: ");
    scanf(" %d ", &d);

    r = n-1;

    while(1<=r){
        m=(r+1)/2;
        if(a[m]==d){
            printf("Given data position is at: ",m+1);
            break;
        }
        else if (a[m]<d){
            l=m+1;
        }
        else if (a[m]<d){
            l=m-1;
        }
    }
    if(l>r){
        printf("NOT FOUND! ");
    }
        return 0;


}

