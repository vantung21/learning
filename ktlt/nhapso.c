#include<stdio.h>
int main(){
    long a=0,s=0; 
    while(a!=(-1)){
        scanf("%ld",&a);
        s+=a;
    }
    printf("%ld",s+1);
}