#include<stdio.h>
int main(){
    long n,m;
    long long tong=0;

    scanf("%ld",&n);
    for(int i=0; i<n;i++){
        scanf("%ld",&m);
        if(m%2==0){
            tong+=m;
        }

    }
    printf("%lld",tong);
}