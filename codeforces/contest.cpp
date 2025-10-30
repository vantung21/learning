#include<bits/stdc++.h>

using namespace std;


int main(){
    int t; cin >> t;
    while(t--){
        int n; cin >> n;
        vector<int> a(n);
        int mx = 0;
        map<int, long long> M;
        for(int i = 0; i<n; i++){
            cin >> a[i];
            M[a[i]]++;
            mx = max(mx, a[i]);
        }

        long long alice = 0, bob = 0;
        bool turnalice = true;
        for(int val = mx; val >=1; val--){
            if(M[val] > 0){
                if(turnalice) alice += M[val];
                else bob += M[val];
                M[val-1] += M[val];
                turnalice = !turnalice;
            }
        }
        cout << alice << " " << bob << "\n";
    }

     
    return 0;
}
