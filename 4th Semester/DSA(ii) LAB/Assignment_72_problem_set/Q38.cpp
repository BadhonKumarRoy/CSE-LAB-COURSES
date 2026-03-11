#include<iostream>
using namespace std;
int Leap_year_tester(int year)
{
    if((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        return 1;
    else
        return 0;
}
int main()
{
    int year;
    cin >> year;
    if(Leap_year_tester(year) == 1)
        cout << "LEAP YEAR" << endl;
    else
        cout << "NORMAL YEAR" << endl;
    return 0;
}