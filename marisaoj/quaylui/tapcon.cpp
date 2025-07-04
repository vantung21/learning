#include <bits/stdc++.h>
using namespace std;

void out(int k, int a[]){
    for(int i = 1; i<= k; i++){
        cout << a[i] << " ";
    }
    cout <<"\n";
}
void Try(int n, int k, int a[], int i){
    for(int j = a[i-1]+1; j <= n-k+i; j++){
        a[i] = j;
        if(i==k){
            out(k, a);
        }
        else Try(n, k, a, i+1);
    }
}
int main(){
    int n, k, a[1000000];
    a[0] = 0;
    cin >> n >> k;
    Try(n,k,a,1);

    return 0;
}