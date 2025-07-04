#include <bits/stdc++.h>
using namespace std;

int visited[1000000] = {0};
void out(int k, int a[]){
    for(int i = 1; i<= k; i++){
        cout << a[i] << " ";
    }
    cout <<"\n";
}

void Try(int n, int k, int a[], int i){
    for(int j = 1; j <= n; j++){
        if(!visited[j]){
            a[i] = j;
            visited[j] = 1;
            if(i == k){
                out(k,a);
            }
            else{
                Try(n,k,a,i+1);
            }
            visited[j] = 0;
        }
    }
}

int main(){
    int n,k;
    cin >> n >> k;
    int a[100000];
    Try(n,k,a,1);


    return 0;
}