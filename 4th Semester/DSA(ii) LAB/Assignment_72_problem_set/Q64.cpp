#include <bits/stdc++.h>
using namespace std;

int main() {
    long long a, b, c, d;
    cin >> a >> b;
    cin >> c >> d;

    long long A = a * c;
    long long C = b * d;

    long long g = __gcd(A, C);
    A /= g;
    C /= g;

    cout << A << " " << C << endl;

    return 0;
}