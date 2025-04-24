#include<iostream>
using namespace std;
int prime[1000001];
void sieve(){
    for(int i=2; i<=1000000; i++){
        prime[i]=1;
    }
    prime[0]=prime[1]=0;
    for(int i=2; i<=1000; i++){
        if(prime[i]){
            for(int j=i*i; j<=1000000; j+=i){
                prime[j]=0;
            }
        }
    }
}
int main(){
    freopen("sortprime.inp","r",stdin);
    freopen("sortprime.out","w",stdout);
    int a[100000], s=0;
    int n;
    sieve();
    cin>>n;
    for(int i=0; i<n; i++){
        cin>> a[i];
        s+=a[i];
    }
    int d1=0, d2=0;
    for(int i=0; i<n; i++){
        if(a[i]==1) d1++;
        if(a[i]==2) d2++;
    }
    if(d1==0){
        cout <<1;
        return 0;
    }
    int cnt=0;
    for(int i=2; i<=s; i++){
        if(prime[i]) cnt++;
    }
    cout << cnt ;
}