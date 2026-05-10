// QuickSort using Lomuto Partitioning

#include <iostream>

using namespace std;

int pivotPartition(int a[], int low, int high){

    int pivot = a[high];
    int i = low - 1;

    for(int j=low; j<high; j++){
        if( a[j] < pivot )
            swap(a[j], a[++i]);
    }

    swap(a[++i], a[high]);
    return i;
}

void quickSort( int a[], int low, int high ){
    if(low < high){
        int pi = pivotPartition(a, low, high);
        quickSort(a, low, pi - 1);
        quickSort(a, pi + 1, high);
    }
}

int main(){
    int a[] = {5, 2, 10, 7, 1, 3, 6, 4};

    // Parameters are quickSort(array, lowest index, highest index)
    quickSort(a, 0, 7);

    for(int i=0;i<8;i++)
        cout << a[i] << " ";
}
