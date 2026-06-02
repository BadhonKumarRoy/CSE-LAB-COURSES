// What problem is this?
// You have:
// items with weight
// items with profit (value)
// a bag with capacity = 8

// Goal:
// Get maximum profit without exceeding capacity
// (you can take each item once or not at all)

// 0/1 Knapsack using Dynamic Programming
// k[i][w] stores maximum profit using first i items with capacity w
// At each step: choose max of (take item, not take item)
// Time Complexity: O(n * capacity)
#include <iostream>
using namespace std;
int main(){

    int n=4;
    int weight[n+1]= {2,3,4,5};
    int profit[n+1]= {1,2,5,6};
    int cap=8;

    int k[n+1][cap+1];

    for (int i=0; i<=n; i++){
        for (int w=0; w<=cap; w++){

            if (i==0 || w==0)
                k[i][w]=0;
            else if (weight[i]>w)
                k[i][w]=k[i-1][w];
            else
                k[i][w]= max(k[i-1][w], k[i-1][w-weight[i]]+profit[i]);
        }
    }
    cout << k[n][cap];



}
