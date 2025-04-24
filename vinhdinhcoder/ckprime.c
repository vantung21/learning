#include<stdio.h>
#include<math.h>
int prime(long long n){
    if(n==0||n==1||n%2==0) return 0;
    if(n==2) return 1;
    for(long i=3; i<=sqrt(n);i+=2){
        if(n%i==0) return 0;
    }
    return 1;
}
int main(){
    freopen("ckprime1.inp","r",stdin);
    freopen("ckprime1.out","w",stdout);
    long long n;
    scanf("%lld",&n);
    if(prime(n)) printf("YES");
    else printf("NO");
}