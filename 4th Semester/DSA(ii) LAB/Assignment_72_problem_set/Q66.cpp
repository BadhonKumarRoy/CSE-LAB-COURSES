#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, mul = 1;
    cin >> n;
    int a[n];
    for(int i = 0; i < n; i++){
        cin >> a[i];
        mul *= a[i];
    }
    cout << mul%10 << endl;

    return 0;
}
