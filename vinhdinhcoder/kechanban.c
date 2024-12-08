#include<stdio.h>
int main(){
    long long a,b,i=0;
    scanf("%lld%lld",&a,&b);
    while(a<=b){
        a+=a;
        i++;

    }
    a/=2;
    i--;
    printf("%lld",i);
}