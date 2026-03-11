#include<iostream>
#include <iomanip>
using namespace std;
int main()
{
    int pA, rI, t;
    cin >> pA >> rI >> t;
    float si = (pA * rI * t) / 100;
    cout << fixed << setprecision(1) << si << endl;
    return 0;
}