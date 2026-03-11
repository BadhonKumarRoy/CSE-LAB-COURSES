#include<bits/stdc++.h>
using namespace std;
int main()
{
    int number;
    cin >> number;
    if(number > 0)
        cout << "POSITIVE" << endl;
    else if(number < 0)
        cout << "NEGATIVE" << endl;
    else
        cout << "ZERO" << endl;
    return 0;
}