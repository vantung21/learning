#include<iostream>
#include<math.h>
#include<string>
using namespace std;

int main(){
    // long long n;
    // cin >> n;
    long long s = 0, base =1 ;
    string A;
    cin >> A;
    for(int i=A.length()-1; i>= 0; i--){
        if(A[i] == '0'){
            base *= 2; continue;
        }
        else {
            s+= base;
            base *=2;
        }
    }
    cout << s;


    return 0;
}