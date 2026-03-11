#include<bits/stdc++.h>
using namespace std;
int main()
{
    string s;
    cin >> s;
    int n = stoi(s);
    int rem, min = 1000000000;
    while(n!= 0)
    {
        rem = n % 10;
        n /= 10;
        if(rem < min)
            min = rem;
    }
    string min_str = to_string(min);
    int pos = s.find(min_str);
    s.erase(pos, 1);
    
    cout << s << endl;
    return 0;
}