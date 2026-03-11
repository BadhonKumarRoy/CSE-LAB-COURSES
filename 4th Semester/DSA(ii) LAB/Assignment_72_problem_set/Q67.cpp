#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    int power, i=0;
    while(power <= n){
        power = pow(2,i++);
        if(power == n){
            cout << "YES" << endl;
            return 0;
        }
    }
    cout << "NO" << endl;
    return 0;
}
