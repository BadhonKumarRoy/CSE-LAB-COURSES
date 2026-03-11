#include<iostream>
using namespace std;
int main()
{
    int a, b, GCD;
    cin >> a >> b;
    for(int i = 1; i <= b; i++)
    {
        if(a % i == 0 && b % i == 0)
        {
            GCD = i;
        }
    }
    cout << GCD << endl;
    return 0;
}