#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    int power, i=0, x;
    while(power <= n){
        power = pow(2,i++);
        if(power <= n){
            x = n - power;
        }
    }
    cout << x << endl;
    return 0;
}
