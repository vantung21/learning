#include <bits/stdc++.h>
using namespace std;

int n,k,f,x = 0;
vector<int> a,place;
vector<bool> used;

bool chia(int cnt, int sum){
    if(sum > f) return false;
    else if(sum == f ){
        if(cnt == k-1) return true;
        if(chia(cnt+1, 0)) return true;
    }
    for(int i = 0; i<n; i++){
        if(used[i]) continue;
        used[i] = true;
        place[i] = cnt;
        if(chia(cnt, sum + a[i])) return true;

        used[i] = false;
    }
    return false;
}

int main(){
    cin >> n >> k;
    a.resize(n,0);
    place.resize(n,0);
    used.resize(n, false);

    for(int i = 0; i<n; i++){
        cin >> a[i];
        x += a[i];
    }
    
    if(x%k != 0){
        cout << "ze" <<endl;
        return 0;
    }
    f = x/k;
    if(chia(0, 0)) {
        for(int i =0; i<n; i++){
            cout << place[i] +1 << " ";
        }
        cout << endl;
        return 0;
    }

    cout << "ze" <<endl;


    return 0;
}