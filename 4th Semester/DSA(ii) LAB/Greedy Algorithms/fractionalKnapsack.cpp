// Selecting Items by value/weight Ratio - O(nlogn) Time and O(n) Space

// The idea is to always pick items greedily based on their value-to-weight ratio. Take the item with the highest ratio first, then the next highest, and so on, until the knapsack is full. If any item doesn’t fully fit, then take its fractional part according to the remaining capacity.

// Steps to solve the problem:

// 1. Calculate the ratio (value/weight) for each item.
// 2. Sort all the items in decreasing order of the ratio.
// 3. Iterate through items:
//    if the current item fully fits, add its full value and decrease capacity otherwise, take the fractional part that fits and add proportional value.
// 4. Stop once the capacity becomes zero.

#include <iostream>
#include <algorithm>

using namespace std;

struct Item{
    int value;
    int weight;
};

bool compare(Item a, Item b){
    double r1= (double)a.value/a.weight;
    double r2= (double)b.value/b.weight;
    return r1>r2;
}

double fractionalKnapsack(int capacity, Item items[],int n){
    sort(items, items+n, compare);
    double totalProfit= 0.0;
    int rem_cap = capacity; // Remaining Capacity is initialized to the total capacity of the knapsack

    for(int i=0;i<n;i++){
        if (items[i].weight <= rem_cap){
            rem_cap -= items[i].weight;
            totalProfit += items[i].value;
        } else {
            totalProfit += rem_cap * (double) (items[i].value / items[i].weight);
            break;
        }
    }

    return totalProfit;
}

int main(){
    int capacity;
    cout << "Enter the capacity of the knapsack: ";
    cin >> capacity;
    int n;
    cout << "Enter the number of items: ";
    cin >> n;
    Item items[n];
    cout << "Enter the value and weight of each item:" << endl;
    for(int i = 0; i < n; i++){
        cin >> items[i].value >> items[i].weight;
    }

    cout << "Maximum Value: " <<fractionalKnapsack(capacity,items,n);

    return 0;
}

    // int capacity= 15;
    // Item items[]= {{10,1},{5,2},{15,5},{7,7},{6,1},{18,4},{3,1}};