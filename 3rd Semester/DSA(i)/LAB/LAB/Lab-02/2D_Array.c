#include<stdio.h>
int main()
{

    int arr[10][10],array[10][10],i,j;
    int row,cols;
    printf("Enter the number of rows and columns:");
    scanf("%d %d",&row,&cols);

    for(i=0;i<row;i++){
        for(j=0;j<cols;j++){
            printf("Array[%d][%d]=",i,j);
            scanf("%d",&arr[i][j]);
        }
        printf("\n");
    }
     printf("Enter the number of rows and columns for 2nd Array:");
    scanf("%d %d",&row,&cols);

    for(i=0;i<row;i++){
        for(j=0;j<cols;j++){
            printf("Array[%d][%d]=",i,j);
            scanf("%d",&array[i][j]);
        }
        printf("\n");
    }


    printf("First Array");
      for(i=0;i<row;i++){
        for(j=0;j<cols;j++){
                printf("%d ",arr[i][j]);
        }
        printf("\n");
    }
    printf("Second Array");
       for(i=0;i<row;i++){
        for(j=0;j<cols;j++){
                printf("%d ",array[i][j]);
        }
         printf("\n");
    }
}
