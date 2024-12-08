#include<stdio.h>
int main(){
    long long a,b,i;
    scanf("%lld%lld",&a,&b);
    if(a%6!=0){
   a=a+6-a%6;}
   b=b-b%6;
   i=(b-a)/6+1;
   printf("%lld",i);
}