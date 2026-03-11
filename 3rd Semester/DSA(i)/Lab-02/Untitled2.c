#include<stdio.h>
int main()
{

    int arr[3][4],i,j;
    for(i=0;i<3;i++){
        for(j=0;j<4;j++){
            printf("Array[%d][%d]=",i,j);
            scanf("%d",&arr[i][j]);
        }

    }
      for(i=0;i<3;i++){
        for(j=0;j<4;j++){
                printf("%d\n",arr[i][j]);
        }
    }
}
