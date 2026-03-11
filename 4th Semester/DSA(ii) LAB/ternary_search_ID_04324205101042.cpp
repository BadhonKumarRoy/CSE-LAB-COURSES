// ID: 04324205101042
#include<bits/stdc++.h>
using namespace std;

int ternarySearch(int arr[], int l, int r, int x)
{
    int i = 1;
    while(l <= r){
        int mid1 = l + (r - l) / 3;
        int mid2 = r - (r - l) / 3;
        cout << "mid1: " << mid1 << endl;
        cout << "mid2: " << mid2 << endl;
        cout << "pass -------- " << i++ << endl << endl;
        if(arr[mid1] == x){
            return mid1;
        }
        else if(arr[mid2] == x){
            return mid2;
        }
        else if(x < arr[mid1]){
            r = mid1 - 1;
        }
        else if(x > arr[mid2]){
            l = mid2 + 1;
        }
        else{
            l = mid1 + 1;
            r = mid2 - 1;
        }
    }
    return -1;
}

int main()
{
    int n;
    cout << "Enter the array size: ";
    cin >> n;
    int arr[n];
    cout << "Enter the elements of the array: ";
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    sort(arr, arr + n);
    cout << "Sorted array: ";
    for(int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    int key;
    cout << "Enter the key to search: ";
    cin >> key;
    int result = ternarySearch(arr, 0, n - 1, key);
    if(result == -1) {
        cout << "Element not found in the array." << endl;
    } else {
        cout << "Element found at index: " << result << endl;
    }
    return 0;
}