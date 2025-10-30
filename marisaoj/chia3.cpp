#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin >> n;
    int a[n];
    for(int i =0; i<n; i++){
        cin  >> a[i];
        a[i] %= 3;
    }
    int dem[3] = {0};
    for(int i = 0; i<n; i++){
        dem[a[i]]++;
    }
    int dem0= 0;
    
    if(dem[0] >1) dem0 = (dem[0])*(dem[0]-1)/2;
    int cnt = dem0 + dem[1]*dem[2];
    
    cout << cnt;
    return 0;
}