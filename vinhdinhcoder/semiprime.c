#include<stdio.h>
int prime[5000001];
void sieve(){
    prime[0]=prime[1]=0;
    for(int i=2; i<=5000000; i++){
        prime[i]=1;
    }
    for(int i=0; i*i<=5000000; i++){
        if(prime[i]){
            for(int j=i*i; j<=5000000; j+=i){
                prime[j]=0;
            }
        }
    }
}
int main(){
    freopen("semiprime.inp","r",stdin);
    freopen("semiprime.out","w",stdout);
    sieve();
    int n,cnt=0; scanf("%d",&n);
    long long s=0;
    int a[400000]={0};
    for(int i=2; i<=n/2+1; i++){
        if(prime[i]){
            a[cnt++]=i;
        }
    }
    cnt--;
    for(int i=0; i<=cnt; i++){
        for(int j=i; j<=cnt; j++){
            long long m=1LL*a[i]*a[j];
            if(m<=n){
                s+=a[i]*a[j];
            }
            else break;
        }
    }
    printf("%d %lld",n,s);
}