#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n, pos = 0, element;
    cin >> n;
    int a[n];
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    cin >> element;
    for(int i = 0; i < n; i++){
        if(a[i] == element){
            pos = i+1;
            cout << pos << endl;
            return 0;
        }
    }
    cout << -1 << endl;
    return 0;
}