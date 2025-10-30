// #include<bits/stdc++.h>

// using namespace std;

// int main(){
//     int n,k;
//     cin >> n >> k;
//     long long a[n];
//     for(int i = 0; i<n; i++){
//         cin >> a[i];
//     }
//     int minidx = 0;
//     for(int i = 0; i<n; i++){
//         if(a[minidx] >= a[i]) minidx = i;
//     }
//     int idx  = minidx;
//     long long kq = a[minidx] + k;

//     for(int i =  minidx; i>=0; i--){
//         int t = (a[i] +k- minidx + idx > 0)?a[i] +k- minidx + idx: 0;
//         if(a[i] +t< a[minidx] + k){
//             idx = i;
//             kq = a[i] + t;
//         } 
//     }
    
//     for(int i = minidx + 1; i< min(minidx + k+1, n); i++){
//         int t = k +minidx - i;
//         if((a[minidx] + t  > a[i]) && (a[idx] + (t + idx - minidx > 0)?(t + idx - minidx):0) > a[i] ) kq = a[idx] + (t + idx - minidx > 0)?(t + idx - minidx):0;
//     }

//     cout << kq << endl;

//     return 0;
// }

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int n;
    ll K;
    cin >> n >> K;
    vector<ll> a(n);
    ll mn = LLONG_MAX, mx = LLONG_MIN;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        mn = min(mn, a[i]);
        mx = max(mx, a[i]);
    }
    auto can = [&](ll H) -> bool {
        bool any = false;
        ll L = 0, R = n - 1;
        for (int i = 0; i < n; ++i) {
            if (a[i] < H) {
                ll need = H - a[i];
                if (need > K) return false;
                ll li = i;
                ll ri = i + (K - need);
                if (ri > n - 1) ri = n - 1;
                if (!any) {
                    any = true;
                    L = li; R = ri;
                } else {
                    L = max(L, li);
                    R = min(R, ri);
                }
                if (L > R) return false;
            }
        }
        return true;
    };
    ll lo = mn, hi = mx + K;
    while (lo < hi) {
        ll mid = (lo + hi + 1) / 2;
        if (can(mid)) lo = mid;
        else hi = mid - 1;
    }
    cout << lo << '\n';
    return 0;
}
