#include<iostream>
using namespace std;
int prime[100001];
void sieve(){
    for(int i=2; i<100001; i++){
        prime[i]=1;
    }
    prime[0]=prime[1]=0;
    for(int i=2; i*i<=100000; i++){
        if(prime[i])
        for(int j=i*i; j<=100000; j+=i){
            prime[j]=0;
        }
    }
}
int ckprime(int n){
    for(int i=2; i*i<=n; i++){
        if(n%i==0) return 0;
    }
    return 1;
}
int main(){
    sieve();
    freopen("diviprime.inp","r",stdin);
    freopen("diviprime.out","w",stdout);
    int n;
    cin>> n;
    if(n==1) {
        cout<< 3;
        return 0;
    }
    else if(n==2){
        cout<< 1;
        return 0;
    }
    else if(n>2 && n%2==0){
        cout<< 2;
        return 0;
    }
    else if(n<=100000 &&n%2){
        if(prime[n]){
            cout << 1;
            return 0;
        }
        else if(prime[n-2]){
            cout <<2;
            return 0;
        }
        else{
            cout <<3;
            return 0;
        }
    }
    else if(n>100000 && n%2){
        int ck=1;
        for(int i=2; i*i<=n; i++){
            if(prime[i] && n%i==0){
                ck=0;
            }
        }
        if(ck){
            cout << 1;
            return 0;
        }
        else if(ckprime(n-2)){
            cout<<2;
            return 0;
        }
        else {
            cout << 3;
            return 0;
        }
    }
}