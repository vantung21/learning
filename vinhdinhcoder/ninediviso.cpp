#include<iostream>
#include<cmath>
using namespace std;
int prime[1000001];
void sieve(){
    for(int i=2; i<=1000000;i++){
        prime[i]=1;
    }
    prime[0]=prime[1]=0;
    for(int i=2; i*i<=1000000; i++){
        if(prime[i]){
            for(int j=i*i; j<=1000000; j+=i){
                prime[j]=0;
            }
        }
    }
}
int main(){
    sieve();
    freopen("ninediviso.inp","r",stdin);
    freopen("ninediviso.out","w",stdout);
    int n, a[10000],cnt=0,d=0;
    cin>> n;
    for(int i=2; i*i<=n; i++){
        if(prime[i]){
            a[cnt++]=i;
        }
    }
    for(int i=0; i<cnt; i++){
        if(pow(a[i],8)<=n) d++;
    }
    for(int i=0; i<cnt; i++){
        for(int j=i+1; j<cnt; j++){
            if(i!=j && pow(a[i],2)*a[j]*a[j]<=n){
                d++;
            }
        }
    }
    cout<<d;
    // for(int i=36; i<=n; i++){
    //     int uoc = 0;
    //     for(int j=2;j*j<=i; j++){
    //         if(i%j==0){
    //             uoc++;
    //             if(j!=i/j) uoc++;
    //         }
    //         if(uoc>7) break;
    //     }
    //     if(uoc==7){
    //             cnt++;
    //         }
    // }
    // cout<<cnt;
}