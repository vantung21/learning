#include<iostream>

using namespace std;

int main(){
    int a, b, k;
    cin >> a>> b>> k;
    int s;
    a %= b;
    if(a==0){
        cout<< a;
        return 0;
    }
    while(k){
        a *= 10;
        s = a/b;
        a %=b;
        k--;
    }
    cout << s;
    return 0;
}