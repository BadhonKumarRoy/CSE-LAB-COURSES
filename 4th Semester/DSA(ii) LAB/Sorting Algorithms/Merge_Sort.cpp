#include <iostream>

using namespace std;

void mergeArray(int a[], int low, int mid, int high){
    int L = low, R = mid+1, k = 0;
    int ia[high-low+1];

    for(int i=low; i<=high; i++){
        if( L > mid ) ia[k++] = a[R++];
        else if( R > high) ia[k++] = a[L++];
        else ia[k++] = a[L] < a[R]? a[L++] : a[R++];
    }

    for(int i=0; i<high-low+1; i++){
        a[low+i] = ia[i];
    }
}

void mergeSort(int a[], int low, int high){
    if(low < high){
        int mid = (low+high)/2;

        mergeSort(a, low, mid);
        mergeSort(a, mid+1, high);
        mergeArray(a, low, mid, high);
    }
}

int main(){
    int a[] = {5, 2, 10, 7, 1, 3, 6, 4};

    // Parameters are mergeSort(array, lowest index, highest index)
    mergeSort(a, 0, 7);

    for(int i=0; i<8; i++)
        cout << a[i] << " ";
}
