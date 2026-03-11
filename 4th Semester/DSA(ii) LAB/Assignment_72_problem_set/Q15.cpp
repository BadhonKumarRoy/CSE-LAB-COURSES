#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin >> n;
    if(n % 2 == 0 && n > 0)
        cout << "Positive & Even" << endl;
    else if(n % 2 != 0 && n > 0)
        cout << "Positive & Odd" << endl;
    else if(n < 0)
        cout << "Negative" << endl;
    else
        cout << "Zero" << endl;
    return 0;
}