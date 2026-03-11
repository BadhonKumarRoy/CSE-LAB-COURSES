#include<bits/stdc++.h>
using namespace std;
int main()
{
    double temperature_in_celsius;
    cin >> temperature_in_celsius;
    double temperature_in_fahrenheit = (temperature_in_celsius * 9.0 / 5.0) + 32.0;
    cout << fixed << setprecision(1) << temperature_in_fahrenheit << endl;
    return 0;
}