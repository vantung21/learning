#include<bits/stdc++.h>
using namespace std;

long long M = 0;
long long w[22], v[22];
long long n,s;
void Try(long long idx, long long g, long long d){
    if(g > s) return;
    if(idx == n){ 
        
        M = max(M, d);
        return;
    }

    // ko chon
    Try(idx +1, g, d);

    //chon
    if(g + w[idx] <= s)
        Try(idx + 1, g + w[idx], d + v[idx]);
}

int main(){
    
    cin >> n >>s;
    
    for(int i = 0; i <n; i++){
        cin >> w[i] >> v[i];
    }

    Try(0, 0, 0);
    cout << M << endl;
    return 0;
}