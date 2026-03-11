#include<bits/stdc++.h>
using namespace std;
int main()
{
    string s, s1="";
    getline(cin, s);
    for(auto i : s){
        if(i >= 'a' && i <= 'z'){
            s1 += toupper(i);
        }
        else if(i >= 'A' && i <= 'Z'){
            s1 += tolower(i);
        }
    }
    cout << s1;
    return 0;
}