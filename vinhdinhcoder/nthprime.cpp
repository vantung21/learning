#include<iostream>
#include<cmath>
using namespace std;
int prime[2000000];
void sieve(){
    for(long i=2; i<2000000 ;i++){
        prime[i]=1;
    }
    prime[0]=prime[1]=0;
    for(long i=2;i<sqrt(2000000);i++){
        for(long j=i*i;j<2000000;j+=i){
            prime[j]=0;
        }
    }
}
int main(){
    freopen("nthprime.inp","r",stdin);
    freopen("nthprime.out","w",stdout);
    sieve();
    int t;
    cin>>t;
    while(t--){
        int cnt=0,n,i=0;
        cin>>n;
        while(cnt<n){
            if(prime[i]){
                cnt++;
            }
            i+=1;
        }
        cout<<i-1<<endl;
    }
}