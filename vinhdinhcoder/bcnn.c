#include<stdio.h>
int main(){
    long long a,b,ucln,m,n;
    scanf("%lld%lld",&a,&b);
    m=a;
    n=b;
    
    while(a!=b && a!=0 &&b!=0){
        if(a>b){
            ucln=b;
            a%=b;

        }
        else{
            ucln=a;
            b%=a;
        }
    }
    m/=ucln;
    n/=ucln;
    printf("%lld",m*n*ucln);
}