#include<bits/stdc++.h>
using namespace std;
int main()
{
    int temperature_in_Celsius;
    cin >> temperature_in_Celsius;
    if(temperature_in_Celsius >= 20) cout << "Hot" << endl;
    else if(temperature_in_Celsius > 9 && temperature_in_Celsius < 20) cout << "Cool" << endl;
    else if(temperature_in_Celsius < 10) cout << "Cold" << endl;
    return 0;
}