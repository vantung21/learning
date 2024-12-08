#include<stdio.h>
int main(){
    int n;
    scanf("%d",&n);
    long long t=1,s=0,d;
    for(int i=1;i<=n;i++){
        d=t+s;
        printf("%lld\t",d);
        t=s;s=d;

    }
}