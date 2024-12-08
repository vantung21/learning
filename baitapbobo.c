#include <stdio.h>
int main(){
    long long n,k,i=1,j=0;
    scanf("%lld %lld",&n,&k);
    for (i;i<=k;i+=3){
        k-=i;
        j++;
        if (j=n){
        break;}
        
    }
printf("%lld",j);
}
