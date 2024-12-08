#include<stdio.h>
int main(){
    long long a,s=1,i=3;
    scanf("%lld",&a);
    while(s<a){
        s+=i;
        i+=2;
    }
    printf("%lld",s);
}