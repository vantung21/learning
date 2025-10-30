#include<bits/stdc++.h>
using namespace std;

int n,m;
int dx[] = {1, 1, 2, 2, -1, -1, -2, -2};
int dy[] = {2, -2, 1, -1, 2, -2, 1, -1};
int a[9][9];

int dem(int x, int y){
    int cnt = 0; 
    for(int i =0; i<8; i++){
        int nx = x + dx[i], ny = y + dy[i];
        if(nx  > 0 && nx <=n && ny > 0 && ny <=m && a[nx][ny] == 0){
            cnt++;
        }
    }
    return cnt;
}

void rect(int cnt, int x, int y){
    if(cnt == n*m){
        for(int i = 1; i<=n; i++){
            for(int j  =1; j <= m; j++){
                cout << a[i][j] << " ";
            }
            cout <<endl;
        }
        exit(0);
    }
    vector<pair<int, pair<int , int>>> moves;
    for(int i = 0; i< 8; i++){
        int nx = x + dx[i];
        int ny = y + dy[i];
        if(nx > 0 && nx <= n && ny > 0 && ny <= m && a[nx][ny] == 0){
            moves.push_back({dem(nx, ny), {nx, ny}});
            // a[nx][ny] = cnt +1;
            // rect(cnt +1, nx, ny);
            // a[nx][ny] = 0;
        }
    }
    sort(moves.begin(), moves.end());
    for(auto &mv : moves){
        int nx = mv.second.first, ny = mv.second.second;
        a[nx][ny] = cnt + 1;
        rect(cnt +1, nx, ny);
        a[nx][ny] = 0;
    }


}


int main(){
    cin >> n >> m;
    memset(a, 0, sizeof(a));
    
    a[1][1] = 1;
    rect(1,1,1);

    return 0;
}