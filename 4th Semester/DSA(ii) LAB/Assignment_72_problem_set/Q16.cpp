#include<bits/stdc++.h>
using namespace std;
int main()
{
    string username;
    int password;
    cin >> username >> password;
    if(username == "admin" && password == 1234)
        cout << "Login successful" << endl;
    else
        cout << "Invalid credentials" << endl;
    return 0;
}