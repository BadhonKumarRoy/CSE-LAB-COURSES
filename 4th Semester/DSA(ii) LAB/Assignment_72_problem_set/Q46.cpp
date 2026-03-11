#include<iostream>
using namespace std;
int main()
{
    int n, max, min;
    cin >> n;
    int a[n];
    for(int i = 0; i < n; i++){
        cin >> a[i];
        if(i == 0){
            max = a[i];
            min = a[i];
        }
        if(a[i] > max) max = a[i];
        else if(a[i] < min) min = a[i];
    }
    
    cout << max << " " << min << endl;
    return 0;
}