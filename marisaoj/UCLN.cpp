#include <bits/stdc++.h>
using namespace std;

long long UCLN(long long a, long long b){
   if(b==0) return a;
   return UCLN(b, a%b);
}

int main(){
    long long a, b;
    cin >> a >> b;
    long long uc = UCLN(a,b);
    long long bc;
    bc = a*b/uc;
    cout << uc << " " << bc << endl;

    return 0;
}