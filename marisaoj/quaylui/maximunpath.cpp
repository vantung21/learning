#include<bits/stdc++.h>
using namespace std;

long long a[4][4];
long long s = 0, t = 0;
void lap(int i, int j){
    if(i<4 && j <4){
        t+= a[i][j];
        if(i == 3 && j == 3){
            s = max(s, t);
        }
        lap(i+1, j);
        lap(i, j+1);
        t -= a[i][j];
    }
}
int main(){
    for(int i = 0; i < 4; i++){
        for(int j =0; j<4; j++){
            cin >> a[i][j];
        }
    }
    lap(0, 0 );
    cout << s << endl;

    return 0;
}