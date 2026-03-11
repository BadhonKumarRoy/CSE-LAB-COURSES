#include<iostream>
using namespace std;
int sum_of_digits(int a)
{
    int sum = 0;
    while(a > 0)
    {
        sum += a % 10;
        a /= 10;
    }
    return sum;
}
int main()
{
    int a;
    cin >> a;
    cout << sum_of_digits(a) << endl;
    return 0;
}