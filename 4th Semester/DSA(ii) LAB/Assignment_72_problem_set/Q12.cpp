#include<bits/stdc++.h>
using namespace std;
int main()
{
    double purchased_amount;
    cin >> purchased_amount;
    if(purchased_amount >= 1000)
        cout << fixed << setprecision(1) << purchased_amount - (purchased_amount * 0.1) << endl;
    else
        cout << fixed << setprecision(2) << purchased_amount << endl;
    return 0;
}