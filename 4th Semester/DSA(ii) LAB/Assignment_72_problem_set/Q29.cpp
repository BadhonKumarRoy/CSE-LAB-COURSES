#include<iostream>
#include <iomanip>
using namespace std;
int main()
{
    float weight, height;
    cin >> weight >> height;
    float bmi = weight / (height * height);
    cout << fixed << setprecision(3) << bmi << endl;
    return 0;
}