#include<stdio.h>
int main(){
    long long x,y,n,a,b;
    
    scanf("%lld%lld%lld",&n,&a,&b);
    x=n/a;
    y=n/b;
    long long p=a,q=b,du;
    while(b!=0){
       du= a%b;
        a=b;b=du;
    }
    p/=a;
    q/=a;
    long long bc=p*q*a;

    long long z,dem=0;
    
    z=n/bc;
    dem=x+y-z;
    
    printf("%lld",dem);
}