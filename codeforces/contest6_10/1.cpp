#include<bits/stdc++.h>
using namespace std;

int main(){

    int t;
    cin >> t;
    while(t--){
        int n,k; 
        cin >> n >> k;
        string s;
        cin >> s;
        int a = 0, b = 0, c = 0;
        for(int i=0; i<k; i++){
            if(s[i] == '0') a++;
            if(s[i] == '1') b++;
            if(s[i] == '2') c++;

        }
        if(k == n){
            for(int i = 0; i<n; i++){
                cout << "-";
            }
            cout <<endl;
            continue;
        }
        int x = n -a- b - 2*c;
        if(a+b+2*c > n) c =n - a - b;
        
        for(int i = 0; i<a; i++) cout << "-";
        if(x < 0){
            for(int i = 0; i< c; i++) cout << "?";
        }
        else{
            for(int i = 0; i< c; i++) cout << "?";
            for(int i = 0; i<x; i++) cout << "+";
            for(int i = 0; i< c; i++) cout << "?";
        }
        for(int i = 0; i< b; i++){
            cout << "-";
        }
        cout << endl;
    }

    return 0;
}