#include<stdio.h>
int main(){
    long long n,gt=1;
    scanf("%lld",&n);
    for(int i=1; i<=n; i++){
        gt*=i;
    }
    printf("%lld",gt);
}