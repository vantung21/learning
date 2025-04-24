#include<iostream>
using namespace std;
int main(){
    int n,a[10001],b[1001]={0};
    cin>> n;
    for(int i=0; i<n; i++){
        cin>> a[i];
        b[a[i]]++;
    }
    int max=0;
    for(int i=0; i<=1000; i++){
        if(b[i]>max) max=b[i];
    }
    cout << max;
    return 0;

}