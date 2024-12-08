#include<stdio.h>
int main(){
    long max,min,n,m;
    scanf("%ld%ld",&n,&m);
    max=m;
    min=m;
    for(int i=2; i<=n; i++){
        scanf("%ld",&m);
        if(m>max) max=m;
        if(m<min) min=m;
    }
    printf("SO LON NHAT: %ld\nSO BE NHAT: %ld",max,min);
}