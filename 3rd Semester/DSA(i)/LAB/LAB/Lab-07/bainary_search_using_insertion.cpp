#include <iostream>
using namespace std;

// Binary Search to find the correct position of the element to be inserted
int binarySearch(int arr[], int low, int high, int key) {
    while (low <= high) {
        int mid = low + (high - low) / 2;

        // Check if key is present at mid
        if (arr[mid] == key)
            return mid;

        // If key is smaller, ignore the right half
        if (arr[mid] > key)
            high = mid - 1;

        // If key is greater, ignore the left half
        else
            low = mid + 1;
    }

    // Return the index where the element should be inserted
    return low;
}

// Insertion Sort using Binary Search
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];

        // Use binary search to find the correct position for key
        int pos = binarySearch(arr, 0, i - 1, key);

        // Shift all elements to the right to make space for the key
        for (int j = i - 1; j >= pos; j--) {
            arr[j + 1] = arr[j];
        }

        // Insert the key at the correct position
        arr[pos] = key;
    }
}

// Function to print the array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int arr[] = {12, 11, 13, 5, 6}; // Example array
    int n = sizeof(arr) / sizeof(arr[0]); // Find the size of the array

    cout << "Original array: ";
    printArray(arr, n);

    // Perform Insertion Sort with Binary Search
    insertionSort(arr, n);

    cout << "Sorted array: ";
    printArray(arr, n);

    return 0;
}

