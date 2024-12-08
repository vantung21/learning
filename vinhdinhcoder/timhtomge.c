#include<stdio.h>
int main(){
    double n,e=1,i=2,lt=4;
    scanf("%lf",&n);
    while(e<=n){
        e+=1/lt;
        i++;
        lt=i*i;

    }
    printf("%.9lf",e);
}