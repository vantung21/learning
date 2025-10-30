#include<bits/stdc++.h>
using namespace std;

int n, m , q;
int I[8], J[8], K[8];
int cnt = 0;
int a[8] = {0};

void Try(int i){
    for(int j = 1; j<=m; j++){
        a[i] = j;
        
        if(i == n){
            bool check = true;
            for(int k = 0;  k<q; k++){
                if(a[I[k]] + a[J[k]] == K[k]) continue;
                check = false;
            }
            if(check) cnt++;
        }
        else Try(i+1);
    }
}


int main(){
    cin >> n >> m >> q ;
    for(int i = 0; i<q; i++){
        cin >> I[i] >> J[i] >> K[i];
    }
    Try(1);
    cout << cnt <<endl;

    return 0;
}