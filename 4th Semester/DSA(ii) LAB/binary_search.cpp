#include<bits/stdc++.h>
using namespace std;

int binarySearch(int arr[], int l, int r, int x)
{
    int i = 1;
    while(l<=r){
        int mid = l + (r - l) / 2;
        cout << "mid: " << mid << endl;
        cout << "pass -------- " << i++ << endl << endl;
        if(arr[mid] == x){
            return mid;
        }
        else if(arr[mid] < x){
            l = mid + 1;
        }
        else r = mid - 1;
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
    int result = binarySearch(arr, 0, n - 1, key);
    if(result == -1) {
        cout << "Element not found in the array." << endl;
    } else {
        cout << "Element found at index: " << result+1 << endl;
    }
    return 0;
}