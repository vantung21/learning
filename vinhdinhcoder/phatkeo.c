#include<stdio.h>
int main(){
    long long n,s=1,k=1;
    scanf("%lld",&n);
    for(int i=2; i<=n; i+=1){
        k+=3;
        s+=k;
    }
    printf("%lld",s);
}