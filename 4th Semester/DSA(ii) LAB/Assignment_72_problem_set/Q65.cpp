#include <bits/stdc++.h>
using namespace std;

int main() {
    int co = 0;
    string s;
    cin >> s;
    for(int i = 0; i < s.size(); i++) {
        if(s[i] == '0') {
            co++;
        }
    }
    int pos = s.find('0');
    s.erase(pos, s.size());
    cout << s << " x 10 ^ " << co << endl;
    return 0;
}