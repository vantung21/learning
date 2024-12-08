#include <stdio.h>
int main(){
    double x;
    long n,gt=1;
    scanf("%lf%ld",&x,&n);
    double s3=1;
    for(int i=1; i<=n; i++){
        x*=i;
        gt*=i;
        s3+=(x/gt);

    }
    printf("%.2lf",s3);
}