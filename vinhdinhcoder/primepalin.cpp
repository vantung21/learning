#include<iostream>
#include<cmath>
using namespace std;
int ckdao(int x){
    int a=0, m=x;
    while(x){
        a=a*10+x%10;
        x/=10;
    }
    if(a==m) return 1;
    else return 0;
}
int ckprime(int n){
    if(n==0||n==1||n%2==0) return 0;
    if(n==2) return 1;
    for(long i=3; i<=sqrt(n);i+=2){
        if(n%i==0) return 0;
    }
    return 1;
}
int main(){
    freopen("primepalin.inp","r",stdin);
    freopen("primepalin.out","w",stdout);
    int n; 
    cin>> n;
    while(1){
        if(ckdao(n+1)&&ckprime(n+1)){
            cout<<n+1;
            break;
        }
        n++;
    }
}