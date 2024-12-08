#include<stdio.h>
int main(){
    double x;
    int n;
    scanf("%lf%d",&x,&n);
    double lt=x,s=1;
    long long gt=1;
    for (int i=1; i<=n; i++){
        s+=(lt/gt);
        lt*=x;
        gt*=(i+1);
    }
    printf("%.2lf",s);
}