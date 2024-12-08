#include <stdio.h>
int main(){
    long n;
    scanf("%ld",&n);
    for(long i =1; i<=(n/2); i++){
        if(n%i==0){
            printf("%ld\t",i);
        }
    }
    printf("%ld",n);

}