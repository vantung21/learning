#include<stdio.h>
int main(){
    long long m,n,k,du;
    scanf("%lld%lld%lld",&m,&n,&k);
    m%=k;
    du=m;
    for(long i=2; i<=n; i++){
        du=(du*m)%k;
    }
    printf("%lld",du);
}