#include<stdio.h>
int bainary_search(int arr[],int n,int data){

    int l,r,m;
    l=0;
    r=n-1;

    while(l<=r){
        m=l+r/2;
        if(data==arr[m]){
            return m;
        }
        else if(data>arr[m]){
            l=m+1;
        }
        else{
            r=m-1;
        }
    }
    return -1;


}
int main(){

    int n,data,i,result;
    printf("Number of element: ");
    scanf("%d",&data);
    int arr[n];
    printf("Enter %d shorted elements: ");

    for(i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }

    printf("Enter searching element: ");
        scanf("%d",&data);
        result = bainary_search(arr,n,data);
        if(result!=-1){
            printf("data found at index %d", result);
    }
    else{
        printf("data not found");
    }

}

