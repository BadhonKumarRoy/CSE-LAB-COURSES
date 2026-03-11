#include<stdio.h>
int main()
{

    int arr[10][10],array[10][10],i,j;
    int row,cols,sum[10][10],sub[10][10];
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
        for(i=0;i<row;i++){
        for(j=0;j<cols;j++){
            sum[i][j]= arr[i][j] + array[i][j];
        }
    }
        for(i=0;i<row;i++){
        for(j=0;j<cols;j++){
            sub[i][j]= arr[i][j] - array[i][j];
        }
    }



    printf("Sum of two array:  \n");
     for(i=0;i<row;i++){
        for(j=0;j<cols;j++){
            printf("%d ", sum[i][j]);
        }
        printf("\n");
    }
      printf("sub of two array:  \n");
     for(i=0;i<row;i++){
        for(j=0;j<cols;j++){
            printf("%d ", sub[i][j]);
        }
        printf("\n");
    }


}
