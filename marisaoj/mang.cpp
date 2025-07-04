#include <bits/stdc++.h>
using namespace std;

int main(){
    long long a[1000000];
    long long n, Min = 0;
    cin >> n;
    long long max = -99999999;
    int index = -1;
    
    for(int i=0; i<n; i++){
        cin >> a[i];
        if(a[i] > max){
            max = a[i];
            index = i;
        }
    }
    cout << max << " " << index;
   

    return 0;
}