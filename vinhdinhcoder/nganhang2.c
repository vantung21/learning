#include<stdio.h>
int main(){
    long n,m,t;
    scanf("%ld%ld",&n,&m);
    t=n;
    int i=0;
    while(t<m){
        if(t%10<5){
            t+=(t/10);
        }
         else if(t%10>=5){
            t+=(t/10)+1;
        }
        i++;
    
    }
    printf("%d",i);
}