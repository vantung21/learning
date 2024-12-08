#include<stdio.h>
int main(){
    long n=1,s=0;
    while(n!=0){
        scanf("%ld",&n);
        if(n%2!=0){
            s++;

        }

    }
    printf("%ld",s);
}