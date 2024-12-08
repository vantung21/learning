#include<stdio.h>
int main(){
    long long n,a,s=0;
    scanf("%lld",&n);
    a=n;
    while(a!=0){
        s+=a%10;
        a/=10;
    }
    if(n%s==0){
        printf("%d",1);
    }
    else{
        printf("%d",0);
    }
}