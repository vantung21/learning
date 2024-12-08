#include<stdio.h>
int main(){
    long long a,b,du;
    scanf("%lld%lld",&a,&b);
    while(b!=0){
        du=a%b;a=b;b=du;
    }
    printf("%lld",a);
}