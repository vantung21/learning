#include<stdio.h>
int main(){
    long long n,k,s=0;
    scanf("%lld%lld",&n,&k);
    for(int i=1; i<=k; i+=3){
        s++;
        k-=i;
        if(s==n){
            break;
        }
    }
    printf("%lld",s);

}