#include <bits/stdc++.h>
using namespace std;

int main(){
    int n, q;
    cin >> n >> q ;
    vector<int> arr(n);
    for(int i = 0; i<n; i++){
        cin >> arr[i];
    }
    int cnt = 0, maxlen = 0;
    for(int i = 0; i<n; i++){
        if(arr[i] > 0 ){
            cnt++;
            if(cnt > maxlen) maxlen = cnt;
        }
        else cnt = 0;
    }
    cout << maxlen << endl;
    
    
    return 0;

}