#include <bits/stdc++.h>
using namespace std;

int main(){
    int n,m;
    cin >> n >> m;
    int arr[n][m];
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            cin >> arr[i][j];
        }
    }
    int t = 0; 
    int d = -1; // chieu
    while(t < n+m-1){
        if(d == 1){
            int i;
            if(t >= m) i=t-m+1;
            else i =0;
            int j = t-i;
            while (j >= 0 && j>= t-n+1){
                cout << arr[i][j] << " ";
                i++; j--;
            }
        }
        else{
            int i;
            if(t >= n) i=t-n+1;
            else i =0;
            int j = t-i;
            while (j >= 0 && j>= t-m+1){
                cout << arr[j][i] << " ";
                i++; j--;
            }
        }
        d = -d;
        t++;
    }
    return 0;
}
