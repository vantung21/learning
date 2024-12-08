#include<stdio.h>
int main(){
    double n,gt=1,s=0;
    scanf("%lf",&n);
    for(int i=1; i<=n; i++){
        gt*=i;
        s=s+(1/gt);

    }
    printf("%.10lf",s);
}