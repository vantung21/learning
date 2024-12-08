#include<stdio.h>
int main(){
    long a,b,n,m,du;
    scanf("%ld%ld",&a,&b);
    n=a;
    m=b;
    while(b!=0){
       du= a%b;
        a=b;b=du;
    }
    n/=a;
    m/=a;

    printf("ucln = %ld\n",a);
    printf("bcnn = %ld",n*m*a);

}