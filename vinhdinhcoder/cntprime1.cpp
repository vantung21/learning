#include<iostream>
using namespace std;
int prime[1000001];
void sieve(){
    for(int i=2; i<=1000000; i++){
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
    freopen("cntprime1.inp","r",stdin);
    freopen("cntprime1.out","w",stdout);
    int k, a, b;
    cin>>k;
    while(k--){
        int cnt=0;
        cin>>a>>b;
        for(int i=a;i<=b;i++){
            if(prime[i]) cnt++;
        }
        cout << cnt<<endl;
    }
}