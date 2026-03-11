#include<bits/stdc++.h>
using namespace std;
int main()
{
    string s;
    cin >> s;
    int count[26] = {0};
    for(auto i : s){
        if(i >= 'A' && i <= 'Z'){
            count[i - 'A']++;
        }
    }
    for(int i = 0; i < 26; i++){
        if(count[i] > 0){
            cout << (char)(i + 'A') << " - " << count[i] << endl;
        }
    }
    return 0;
}