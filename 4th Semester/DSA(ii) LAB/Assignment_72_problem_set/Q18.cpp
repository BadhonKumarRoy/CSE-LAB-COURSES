#include<bits/stdc++.h>
using namespace std;
int main()
{
    int side1, side2, side3;
    cin >> side1 >> side2 >> side3;
    // valid_triangle
    if(side1 + side2 > side3 && side2 + side3 > side1 && side1 + side3 > side2){
        if(side1 == side2 && side2 == side3)
            cout << "Equilateral" << endl;
        else if(side1 == side2 || side2 == side3 || side1 == side3)
            cout << "Isosceles" << endl;
        else
            cout << "Scalene" << endl;
    }
    return 0;
}