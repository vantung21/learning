#include<stdio.h>
int main(){
    int n;
    scanf("%d",&n);
    int kq=0;
    for(int i=1; i<=n; i++){
        kq+=kq+1;
    }
    printf("%d",kq);
}

