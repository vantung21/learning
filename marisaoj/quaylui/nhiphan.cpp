#include<bits/stdc++.h>
using namespace std;

void out(int a[], int n){
    for(int i =1; i<=n; i++){
        cout << a[i] ;
    }
    cout << endl;
}

void Try(int i, int a[], int n){
    for(int j = 0 ; j <=1; j++){
        a[i] = j;
        if(i == n){
            out(a,n);
        }
        else{
            Try(i+1, a, n);
        }
    }
}
int main(){
    int n; cin >> n;
    int a[n];
    Try(1,a,n);

    return 0;
}