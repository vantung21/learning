#include <bits/stdc++.h>
using namespace std;


void Try(int n, string s){
    if(s.size() == n){
        cout << s << endl;
        return;
    }
    else{
        for(char x : {'A', 'B', 'C'}){
            if(s.empty() || s.back() != x){
                Try(n, s + x);
            }
        }
    }
}

int main(){
    int n;
    cin >> n;
    string s = "";
    Try(n, s);
    return 0;
}