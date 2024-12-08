#include<stdio.h>
int main(){
    long n, s=0;
    scanf("%ld",&n);
    
    while(n!=0){
        s+=n%10;
        n/=10;
    }
    if(s%10==9){
        printf("YES");
    }
    else printf("NO");
}