#include<bits/stdc++.h>
using namespace std;
int n, a[10], cnt =0;

void Try(int i){
    for(int j = a[i-1]+1; j<n; j++){
        a[i] = j;
        if(i == 3){
            n -= a[i];
            if(a[i] < n) cnt++;
        }
        else{
            n -=a[i];
            Try(i+1);
        }
        n +=a[i];
    }
}
int main(){
    a[0] = 0;
    cin >> n;
    Try(1);
    cout << cnt <<endl;
    return 0;
}