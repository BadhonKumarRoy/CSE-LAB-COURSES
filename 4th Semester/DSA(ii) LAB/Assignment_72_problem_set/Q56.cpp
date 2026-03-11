#include<bits/stdc++.h>
using namespace std;
int main()
{
    string s, s1="";
    getline(cin, s);
    for(auto i : s){
        if(i >= 'a' && i <= 'z'){
            s1 += i;
        }
    }
    cout << s1;
    return 0;
}