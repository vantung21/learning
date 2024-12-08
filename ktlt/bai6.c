#include<stdio.h>
int main(){
    long long n,m,g;
    scanf("%lld%lld",&n,&m);
    long long t=1,s=0,d;
    for(int i=1;i<=n;i++){
        d=t+s;
        t=s;s=d;
        g=d%m;

    }

    printf("%lld",g);
}