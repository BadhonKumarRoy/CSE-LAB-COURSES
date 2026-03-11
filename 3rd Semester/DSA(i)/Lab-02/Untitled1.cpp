#include<iostream>
using namespace std;
int main()
{
    int arr[3][4],i,j;
   /* cout<<"Enter row";
    cin>>r;
    cout<<"Enter colum";
    cin>>c;*/

    for(i=0;i<3;i++){
        for(j=0;j<4;j++){
            cout<<"array[%d][%d]=",i,j;
            cin>>"%d",&arr[i][j];
        }
        cout<<"\n";
    }
        for(i=0;i<r;i++){
            for(j=0;j<4;j++){
                cout<<"%d",arr[i][j]<<"%d";
            }
        }


}
