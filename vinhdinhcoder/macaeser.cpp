#include<iostream>
#include<string.h>
using namespace std;
int main(){
    char s[1000];
    int k;
    cin>>k>>s;
    k%=26;
    for(int i=0; i<strlen(s); i++){
        s[i]+=k;
        if(s[i]>'Z') s[i]-=26;
    }
    cout << s;
    return 0;
}