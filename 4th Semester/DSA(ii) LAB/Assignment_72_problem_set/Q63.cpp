#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;

    string target = "MANDZUKICNESS";
    int maxMatch = 0;

    for (int n = 1; n <= target.size(); n++) {
        string prefix = target.substr(0, n);

        if (s.find(prefix) != string::npos) {
            maxMatch = n;
        }
    }

    cout << maxMatch << endl;

    return 0;
}