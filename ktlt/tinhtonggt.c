#include<stdio.h>
int main(){
    long long n,s=0,gt=1,t;
    scanf("%lld",&n);
    for(int i=1; i<=n; i++){
        t=i*(i+1)/2;
        gt=1;
        for(int j=1; j<=t;j++){
            gt*=j;
        }
        s+=gt;
    }
    printf("%lld",s);


}