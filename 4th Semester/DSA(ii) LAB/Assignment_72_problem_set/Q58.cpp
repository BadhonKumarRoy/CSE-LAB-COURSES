#include<bits/stdc++.h>
using namespace std;
int main()
{
    string s, s1;
    getline(cin, s);
    s1 = s;
    reverse(s1.begin(), s1.end());
    if(s1 == s){
        cout << "Yes";
    }
    else
        cout << "No";
    return 0;
}