#include <iostream>
#include <string>
using namespace std;

int main() {
    int co = 1;
    string s;
    getline(cin, s);
    for(int i = 0; i < s.size(); i++){
        if(s[i]==' '){
            co++;
        }
    }
    cout << co << endl;
    return 0;
}
