#include <bits/stdc++.h>
using namespace std;


int main(){
    long long n,k, a[100000];
    cin >> n >> k;
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    bool check = false;
    for(int i = 0; i< (1 << n); i++){
        long long s = 0;
        for(int j = 0; j< n; j++){
            if(i & (1 << j)){
                s += a[j];
            }
        }
        if(s == k) check = true;
    }

    if(check){
        cout << "YES";
    }
    else cout << "NO";

    return 0;
}