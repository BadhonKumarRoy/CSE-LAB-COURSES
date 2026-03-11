#include<bits/stdc++.h>
using namespace std;
int main()
{
    int mark;
    cin >> mark;
    if(mark > 89) cout << "A" << endl;
    else if(mark > 79 && mark <= 89) cout << "B" << endl;
    else if(mark > 69 && mark <= 79) cout << "C" << endl;
    else if(mark > 59 && mark <= 69) cout << "D" << endl;
    else cout << "F" << endl;
    return 0;
}