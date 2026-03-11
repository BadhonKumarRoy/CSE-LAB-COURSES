#include<iostream>
using namespace std;
int main()
{

    int n;
    cout<<"Enter array size: ";
    cin>>n;
    int arr[n];

    cout<<"Enter element: ";
    for(int i=0; i<n; i++){
       cin>>arr[i];
    }

    for(int i=0; i<n-1; i++){
        int a=i;
        for(int j=i+1; j<n; j++){
        if(arr[j]<arr[a]){
            a=j;
        }
    }
        swap(arr[i],arr[a]);
    }

    cout<<"sorted array: ";
    for(int i=0; i<n; i++){
        cout<<arr[i]<<" ";
    }


}

