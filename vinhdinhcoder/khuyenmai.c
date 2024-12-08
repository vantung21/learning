#include<stdio.h>
int main(){
    int n,t;
    scanf("%d",&n);
    t=n;
    while(n/10!=0){
        t+=3;
        n-=7;
    }
    printf("%d",t);
}