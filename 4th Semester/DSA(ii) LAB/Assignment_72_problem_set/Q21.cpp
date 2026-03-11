#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n, sum = 0, i = 1;
    cin >> n;
    while(n--)
    {
        sum += i;
        i++;
    }
    cout << sum << endl;
}