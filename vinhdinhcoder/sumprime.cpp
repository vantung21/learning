#include<iostream>
using namespace std;
int prime[1000001];
void sieve(){
    prime[0]=prime[1]=0;
    for(int i=2; i<=1000000; i++){
        prime[i]=1;
    }
    for(int i=2; i*i<=1000000; i++){
        if(prime[i]){
            for(int j=i*i; j<=1000000; j+=i){
                prime[j]=0;
            }
        }
    }
}
int main(){
    freopen("sumprime.inp","r",stdin);
    freopen("sumprime.out","w",stdout);
    sieve();
    int k;
    cin>>k;
    while(k--){
        long long n,s=0;
        cin>>n;
        for(int i=2; i<=n; i++){
            if(prime[i]) s+=i;
        }
        cout<< s<<"\n";
    }
    return 0;
}