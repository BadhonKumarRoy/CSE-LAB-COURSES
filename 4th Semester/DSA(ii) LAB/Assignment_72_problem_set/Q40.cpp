#include<iostream>
using namespace std;
int palindrome_check(int a)
{
    int original = a;
    int reversed = 0;
    while(a > 0)
    {
        reversed = reversed * 10 + a % 10;
        a /= 10;
    }
    return original == reversed;
}
int main()
{
    int a;
    cin >> a;
    if(palindrome_check(a))
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
    return 0;
}