#include<stdio.h>
int main(){
    long long n,s=0;
    scanf("%lld",&n);
    for(int i=1; i<=(n/2); i++){
        if(n%i==0){
            s++;

        }

    }
    printf("%lld",s+1);

}