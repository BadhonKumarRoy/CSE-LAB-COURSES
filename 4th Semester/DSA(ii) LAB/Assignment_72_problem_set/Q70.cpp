#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
    if(n <= 1) return 0;
    else
    {
        for(int i = 2; i < n; i++)
        {
            int co = 0;
            for(int j = 1; j < n; j++)
            {
                if(i % j == 0)
                    co++;
            }
            if(co == 2)
                cout << i << " ";
        }
    }
    return 0;
}
