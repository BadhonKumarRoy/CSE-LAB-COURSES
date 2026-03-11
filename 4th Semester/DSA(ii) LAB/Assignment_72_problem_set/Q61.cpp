#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n, co = 0;
    cin >> n;
    string bi = "";
    while(n > 0){
        bi = to_string(n % 2) + bi;
        n /= 2;
    }
    for(int i = 0; i < bi.length(); i++){
        if(bi[i] == '1'){
            co++;
        }
    }
    cout << co << endl;
     
    return 0;
}