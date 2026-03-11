#include<iostream>
using namespace std;
int prime_num(int a)
{
    for(int i = 2; i < a; i++)
    {
        if(a % i == 0)
        {
            return 0;
        }
    }
    return 1;
}
int main()
{
    int a;
    cin >> a;
    if(prime_num(a) == 1)
        cout << "PRIME" << endl;
    else
        cout << "NOT PRIME" << endl;
    return 0;
}