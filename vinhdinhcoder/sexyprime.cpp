#include<iostream>
#include<cmath>
using namespace std;
int prime[1000001];
void sieve(){
    for(int i=0; i<1000001; i++){
        prime[i]=1;
    }
    prime[0]=prime[1]=0;
    for(int i=2; i<=1000; i++){
        if(prime[i])
            for(int j=i*i; j<=1000000; j+=i){
                prime[j]=0;
            }
    }
}
int main(){
    freopen("sexyprime.inp","r",stdin);
    freopen("sexyprime.out","w",stdout);
    sieve();
    int t;
    cin>>t;
    while(t--){
        int n, cnt=0,i=0;
        cin>>n;
        while(cnt<n){
                if(prime[i]&&prime[i+6]){
                    cnt++;
                }
                i++;
        }
        cout<<i-1<<" "<<i+5<<endl;
    }
}