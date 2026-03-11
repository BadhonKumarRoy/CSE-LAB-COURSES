#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n, co = 0;
    cin >> n;
    int a[n];
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    set <int> s(a, a+n);
    n = s.size();
    for(auto i : s){
        if(co++ == n-2){
            cout << i << endl;
            return 0;
        }
    }
    return 0;
}