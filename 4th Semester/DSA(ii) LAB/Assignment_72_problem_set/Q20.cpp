#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin >> n;
    int i = 1;
    if (n == 1)
    {
        cout << "No even numbers";
        return 0;
    }
    while (n--)
    {
        if (i % 2 == 0)
            cout << i << " ";
        i++;
    }
    cout << endl;
    return 0;
}