#include<bits/stdc++.h>
using namespace std;

int main(){
    long long n;
    cin >> n;
    long long cnt = 0;
    if(n < 3) {
        cout << cnt;
        return 0;
    }
    for(long long i = 2; i*(i-1)/2 <= n; i++){
        long long t = n - ((i-1)*i)/2;
        if( t%i == 0 ) cnt++;
    }
     cout << cnt << endl;
    return 0;
}