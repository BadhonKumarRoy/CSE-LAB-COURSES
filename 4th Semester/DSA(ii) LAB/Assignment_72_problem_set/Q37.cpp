#include<iostream>
#include<iomanip>
using namespace std;
float avg(int a, int b, int c)
{
    return (a + b + c) / 3.0;
}
int main()
{
    int a, b, c;
    cin >> a >> b >> c;
    cout << fixed << setprecision(1) << avg(a, b, c) << endl;
    return 0;
}