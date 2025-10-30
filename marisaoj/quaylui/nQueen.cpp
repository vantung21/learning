#include<bits/stdc++.h>

using namespace std;
int n;
int a[11] = {0}, b[22] = {0}, c[22] = {0};
int cnt = 0;

void lap(int i){
    for(int j = 0; j < n; j++){
        if(a[j] == 0 && b[i + j ] == 0 && c[i - j + n] == 0){
            a[j] = b[i+j] = c[i-j + n] = 1;
            if(i == n-1){
                cnt++;
            }
            else{
                lap(i+1);
            }
            a[j] = b[i+j] = c[i-j + n] = 0;
        }
    }
}


int main(){
    cin >> n;
   
    lap(0);
    cout << cnt << endl;

    return 0;
}