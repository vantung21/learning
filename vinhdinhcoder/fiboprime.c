#include<stdio.h>
long long max(long long a, long long b){
    if(a>b) return a;
    return b;
}
int prime[10000001];
void sieve_prime(long long l, long long r){
    
    for(int i=0; i<=r-l; i++){
        prime[i]=1;
    }
    if(l==1) prime[0]=0;
    for(long long i=2; i*i<=r; i++){
        for(int j=max(i*i,(l+i-1)/i*i); j<=r; j+=i){
            prime[j-l]=0;
        }
    }
}
int fibo[10000001];
void sieve_fibo(long long l, long long r){
    for(int i=0; i<r-l+1; i++) fibo[i]=0;
    long long a=1, b=1, next=0;
    while(next<=r){
        next=a+b; a=b; b=next;
        if(next >= l){
            fibo[next-l]=1;
        }
    }
}
int main(){
    freopen("fiboprime.inp","r",stdin);
    freopen("fiboprime.out","w",stdout);
    long long a,b,cnt =0 ; 
    scanf("%lld%lld", &a,&b);
    sieve_prime(a,b);
    sieve_fibo(a,b);
    for(long long i=a; i<=b; i++){
        if(fibo[i-a] && prime[i-a]) cnt++;
    }
    printf("%lld",cnt);
}