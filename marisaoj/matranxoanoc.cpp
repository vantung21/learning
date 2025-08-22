#include <bits/stdc++.h>
using namespace std;

int main(){
    long long n,m;
    cin >> n >> m;
    int dx[] = {0, 1, 0, -1};
    int dy[] = {1, 0, -1, 0};
    int arr[n+1][m+1] = {};
    int i = 1, j = 1, cur = 1, k = 0;
    while(cur <= n*m){
        arr[i][j] = cur++;
        i+=dx[k]; j += dy[k];
        if(!(i>=1 &&i<=n && j>=1 &&j <= m && !arr[i][j])){
             i-=dx[k]; j-=dy[k];
             k= ++k%4;
             i+=dx[k]; j += dy[k];
        }
    }
    for(int a = 1; a<=n; a++){
        for(int b = 1; b<=m; b++){
            cout << arr[a][b] << " ";
        }
        cout << "\n";
    }

    return 0;
}
