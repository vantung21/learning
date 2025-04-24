#include<iostream>
using namespace std;
int main(){
    string s;
    cin>>s;
    long m=0;
    for(int i=0; i<s.length();i++){
        m=m+s[i]-48;
    }
    cout<<m;
}