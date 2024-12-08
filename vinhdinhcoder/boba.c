#include<stdio.h>
int main(){
    long a,b ,s=0;
    scanf("%ld%ld",&a,&b);
    for(int i=a; i<=b; i++){
        if(i%3==0)
        s++;
    }
    printf("%ld",s);
}