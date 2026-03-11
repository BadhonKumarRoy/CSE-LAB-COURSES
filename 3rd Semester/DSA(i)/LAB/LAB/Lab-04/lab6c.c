#include<stdio.h>
int main(){
int row,col;
for(row=1;row<=3;row--){

    for(col=3;col<=row;col++){
        printf("%d ",col);
    }
   printf("\n");
}
return 0;

}

