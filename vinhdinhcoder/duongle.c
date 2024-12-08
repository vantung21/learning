#include<stdio.h>
int main(){
    long long n,s=0;
    scanf("%lld",&n);
    for(int i=1; i<=n;i+=1){
        if(i%2==1){
            s+=i;
        }
    }
    printf("%lld",s);
} 
#if 0
#include<stdio.h>
int main(){
    long long  n,s=0;
    scanf("%lld",&n);
    if(n%2==0){
        printf("%lld",(n*n)/4);
    }
    if(n%2==1){
        printf("%lld",((n+1)*(n+1))/4);
    }
}
#endif