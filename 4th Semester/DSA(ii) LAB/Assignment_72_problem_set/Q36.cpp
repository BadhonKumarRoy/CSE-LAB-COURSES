#include<iostream>
using namespace std;
int Minute_to_hour_minute(int a)
{
    int hour = a / 60;
    int minute = a % 60;
    cout << hour << " HRS " << minute << " MIN" << endl;
    return 0;
}
int main()
{
    int a;
    cin >> a;
    Minute_to_hour_minute(a);
    return 0;
}