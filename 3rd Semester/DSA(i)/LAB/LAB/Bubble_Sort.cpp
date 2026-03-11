#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cout << "---------- Bubble Sort ----------" << endl;
    cout << endl;
    cout << "Enter a Size for an array: ";
    cin >> n;
    int arr[n];
    cout << "Enter the elements of the array: ";
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }

    for(int i = 0; i < (n-1); i++){
        cout << endl;
        cout << endl;
        cout << "Pass- " << i+1 << endl;
        for(int j = 0; j < n-(i+1); j++){
            if(arr[j] > arr[j+1]){
                swap(arr[j], arr[j+1]);
            }
            for(int k = 0; k < n; k++){
                cout << arr[k] << " ";
            }
            cout << endl;
        }
    }
    cout << endl;
    cout << endl;
    cout << "---------- The sorted array: ";
    for(int i = 0; i < n; i++){
        cout << arr[i] << " ";
    }
    cout << "----------" << endl;
    cout << endl;


    return 0;
}
