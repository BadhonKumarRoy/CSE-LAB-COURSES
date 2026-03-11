#include<iostream>
using namespace std;
int main()
{
    long long n;
    cin >> n;
    string s = to_string(n), s1;
    for(int i = s.length()-1; i>=0; i--)
    {
        s1 += s[i];
    }
    n = stoll(s1);
    cout << n << endl;
}