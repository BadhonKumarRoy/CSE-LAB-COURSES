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

    for (auto i : s){
        if(i < 100) co++;
    }
    cout << co << endl;
    return 0;
}