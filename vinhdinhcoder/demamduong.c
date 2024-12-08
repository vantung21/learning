#include<stdio.h>
int main(){
    int n,m,am=0,d=0;
    scanf("%d",&n);
    for(int i=1; i<=n; i++){
        scanf("%d",&m);
        if(m<0) am++;
        if(m>0) d++;

    }
    printf("SO DUONG: %d\n",d);
    printf("SO AM: %d",am);
}