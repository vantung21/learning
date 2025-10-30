#include<bits/stdc++.h>
using namespace std;



int prefix(int i, string s){
    int t = 0;
    for(int j = 0; j < i; j++){
        if(s[j] == 'a') t++;
        else t--;
    }
    return t;
}

int main(){

    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        string s;  
        cin >> s;
        int diff = prefix(n,s);
        if(diff == 0 ){
            cout << 0 << endl;
            continue;
        }

        unordered_map<int, int> first;
        first[0] = 0;
        int pref = 0, ans = n + 1;

        for (int i = 0; i < n; i++) {
            pref += (s[i] == 'a' ? 1 : -1);
            if (first.find(pref - diff) != first.end()) {
                ans = min(ans, i - first[pref - diff] + 1);
            }
            if (first.find(pref) == first.end())
                first[pref] = i+1;
        }

        if (ans >= n) cout << -1 << "\n";
        else cout << ans << "\n";

    }

    return 0;
}