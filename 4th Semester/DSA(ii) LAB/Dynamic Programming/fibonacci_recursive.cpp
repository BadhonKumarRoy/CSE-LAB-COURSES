#include <iostream>
using namespace std;

long long fib[1000];

long long fibonacci(int n)
{
    if(fib[n] == -1)
        fib[n] = fibonacci(n-1)+fibonacci(n-2);

    return fib[n];
}

int main(){
    for(int i=0;i<1000;i++)
        fib[i] = -1;
    fib[0] = 0;
    fib[1] = 1;
    cout << (fibonacci(999));
}
