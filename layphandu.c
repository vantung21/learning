#include<stdio.h>
int main(){
    unsigned long long m,n,k,kq;
    scanf("%llu %llu %llu",&m,&n,&k);
    kq=m;
    for(int i=1; i<n;i++){
        if(kq>k){
            kq%=k;
        }
        kq*=m;

    }
    printf("%llu",kq%k);
}