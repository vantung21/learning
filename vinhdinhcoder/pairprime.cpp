#include<iostream>
using namespace std;
// int ckprime(int n){
//     if(n==2) return 1;
//     if(n==0||n==1||n%2==0) return 0;
//     for(long i=3; i*i<=n;i+=2){
//         if(n%i==0) return 0;
//     }
//     return 1;
// }
int prime[100001];
void sieve(){
    for(int i=2; i<=100000; i++){
        prime[i]=1;
    }
    prime[0]=prime[1]=0;
    for(int i=2; i*i<=100000; i++){
        if(prime[i]){
            for(int j=i*i; j<=100000; j+=i){
                prime[j]=0;
            }
        }
    }
}
int ck(int b[100000], int cnt, int n){
    if(n<=100000) return prime[n];
    if(n%2==0) return 0;
    if(n%2){
        for(int i=1; i<cnt && b[i]*b[i]<=n; i+=1){
            if(n%b[i]==0) return 0;
        }
        return 1;
    }
    
}
int main(){
    sieve();
    int b[100000], cnt=0;
    for(int i=2;i<100000; i++){
        if(prime[i]){
            b[cnt++]=i;
        } 
    }
    freopen("pairprime.inp","r",stdin);
    freopen("pairprime.out","w",stdout);
    int n,a[100000],d=0;
    cin>>n;
    for(int i=0; i<n; i++){
        cin>>a[i];
        if(ck(b,cnt, a[i])) d++;
    }
    cout << d*(-d-1L+2*n)/2;
    return 0;

}