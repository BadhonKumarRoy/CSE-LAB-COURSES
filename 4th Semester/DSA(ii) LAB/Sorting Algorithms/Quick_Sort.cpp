// QuickSort using Lomuto Partitioning

#include <iostream>

using namespace std;

int pivotPartition(int a[], int low, int high){
    int p = low - 1;

    for(int i=low;i<high;i++){
        if( a[i] < a[high] )
            swap(a[i], a[++p]);
    }

    swap(a[++p], a[high]);
    return p;
}

void quickSort( int a[], int low, int high ){
    if(low < high){
        int pivot = pivotPartition(a, low, high);
        quickSort(a, low, pivot-1);
        quickSort(a, pivot+1, high);
    }
}

int main(){
    int a[] = {5, 2, 10, 7, 1, 3, 6, 4};

    // Parameters are quickSort(array, lowest index, highest index)
    quickSort(a, 0, 7);

    for(int i=0;i<8;i++)
        cout << a[i] << " ";
}
