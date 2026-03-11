#include<iostream>
using namespace std;
int Get_the_Large_Num(int a, int b)
{
    if(a > b) return a;
    else return b;
}
int main()
{
    int a, b;
    cin >> a >> b;
    cout << Get_the_Large_Num(a, b) << endl;
    return 0;
}