#include<stdio.h>
#include<math.h>
int main(){
    long long n,a,i=0;
    scanf("%lld",&n);
    a=n;
    while(a!=0){
        a=a/10;
        i++;
    }
    a=n;
    long long s=0;
    while(a!=0){
        s+=pow((a%10),i);
        a/=10;
    }
    if(s==n){
        printf("YES");
    }
    else{
        printf("NO");

    }


}