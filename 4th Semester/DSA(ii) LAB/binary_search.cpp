#include<bits/stdc++.h>
using namespace std;

int binarySearch(int arr[], int n, int key) {
    int left = 0;
    int right = n-1;

    while(left <= right){
        int mid = left + (right-left)/2;

        if(arr[mid] ==  key)
            return mid;
        else if(arr[mid] < key)
            left = mid+1;
        else if(arr[mid] > key)
            right = mid-1;
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
    int key;
    cout << "Enter the key to search: ";
    cin >> key;
    int result = binarySearch(arr, n, key);
    if(result == -1) {
        cout << "Element not found in the array." << endl;
    } else {
        cout << "Element found at index: " << result+1 << endl;
    }
    return 0;
}