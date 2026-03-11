#include<bits/stdc++.h>
using namespace std;
int main()
{
   int a, b;
   cout<<"Enter two number : " <<endl;
   cin>>a>>b;
   int best = 1;
   for (int c = 1; c<=min(a, b); c++)
   {
       if (a % b == 0 && b % c == 0)
       {
           best = c;
       }
   }
   cout << "GCD of " << a << " and " << b << " = " << best << endl;
   return 0;
}
