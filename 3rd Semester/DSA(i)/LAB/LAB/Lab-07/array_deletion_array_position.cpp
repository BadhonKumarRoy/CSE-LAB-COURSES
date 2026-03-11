#include <iostream>
using namespace std;

int main() {
    int n;

    cout << "Enter the size of the array: ";
    cin >> n;

    int arr[n];
    cout << "Enter " << n << " elements:";
    for (int i=0; i<n; i++) {
        cin >> arr[i];
    }

    int position;
    cout << "Enter the position to delete an element: ";
    cin >> position;

    if (position < 0 || position >= n) {
        cout << "Invalid position!";
    }

    for (int i=position; i<n - 1; i++) {
        arr[i] = arr[i+1];
    }

    n--;

    cout << "Array after deletion: ";
    for (int i=0; i<n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
