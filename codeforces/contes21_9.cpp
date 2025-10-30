#include <bits/stdc++.h>
using namespace std;

int main(){
    int t; cin >> t;
    while(t--){
        int n; cin >> n;
        string s; cin >> s;
        bool ok = true;
        for(int i = 0; i<n; i++){
            if(s[i] == '0'){
                if(i == 0 && s[i+1] =='1'){
                    cout << "NO\n";
                    ok = false;
                    break;
                }
                if(i == n-1 && s[i-1] == '1'){
                    cout << "NO\n";
                    ok = false;
                    break;
                }
                if( s[i-1] == '1' && s[i+1] == '1' ){
                    cout << "NO\n";
                    ok = false;
                    break;
                }
            }

        }
        if(!ok) continue;

        int l = 0; int r = -1;
        for(int i = 0; i<n; i++){
            if(s[i] == '1'){
                int x = l-r;
                while(x-- && l+x <= n){
                    cout << l+x << " ";
                }
                cout << i+1 <<" ";
            }
            else{
                if(l > r) l = i+1;
                r = i+1;
            }
        }

    }
    return 0;
}