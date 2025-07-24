#include <bits/stdc++.h>
using namespace std;

int main(){
    long long n,m,x,y;
    cin >> n >> m>> x >> y;
    long long A[n][m], B[x][y];
    for(int i =0; i<n; i++){
        for(int j =0; j < m; j++){
            cin >> A[i][j];
        }
    }
    for(int i = 0; i<x; i++){
        for(int j = 0; j<y; j++){
            cin >> B[i][j];
        }
    }
    if(n < x || m<y){
        cout << "NO";
        return 0;
    }
    for(int i = 0; i<= n-x;i++){
        for(int j = 0; j <=m-y; j++){
            if(A[i][j] == B[0][0]){
                int t = 1;
                for(int q = 0; q<x; q++){
                    for(int k = 0; k <y; k++){
                        if(A[i+q][j+k] != B[q][k]) t=0;
                    }
                }
                if(t){
                    cout << "YES";
                    return 0;
                }
            }
        }
    }
    cout << "NO";


    return 0;
}
