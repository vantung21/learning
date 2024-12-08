#include <stdio.h>
int main(){
    int n;
    double gt=1;
    scanf("%d",&n);
    
    for(int i=1; i<=n;i++){
        gt*=i;
    }
    printf("%lf",gt);}
