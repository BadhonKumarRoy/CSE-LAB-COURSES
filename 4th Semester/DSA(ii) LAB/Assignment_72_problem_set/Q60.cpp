#include<bits/stdc++.h>
using namespace std;
int main()
{
    string n;
    cin >> n;
    int len = n.length();
    for(int i = 0; i < len; i++){
        cout << n[i];
        if((len - i - 1) % 3 == 0 && i != len - 1){
            cout << ",";
        }
    }
    return 0;
}