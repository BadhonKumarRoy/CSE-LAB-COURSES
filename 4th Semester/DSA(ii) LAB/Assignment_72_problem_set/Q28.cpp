#include<iostream>
#include <iomanip>
using namespace std;
int main()
{
    int r;
    cin >> r;
    float perimeter = 2 * 3.1416 * r;
    cout << fixed << setprecision(4) << perimeter << endl;
    return 0;
}