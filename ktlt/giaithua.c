#include<stdio.h> 
int main(){
    long long n,gt=1;
    scanf("%lld",&n);
    
    for(int i=n;i>=1;i-=2){
        gt*=i;
    }
    printf("%lld",gt);
}