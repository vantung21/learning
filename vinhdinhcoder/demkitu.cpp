#include<iostream>
using namespace std;
int main(){
    int a[1000]={0};
    string s;
    cin >>s;
    for(int i=0; i<s.length(); i++){
        a[s[i]]++;
    }
    for(char i='A'; i<='Z'; i++){
        if(a[i]!=0){
            char c=i;
            cout<< c<<" "<<a[i]<<endl;
        }
    }
}