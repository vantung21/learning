#include<stdio.h>
double tong( long n, long x );
int main(){
    long n,x;
    scanf("%ld %ld",&n,&x);
    printf("%.4lf", tong(n,x));
}
double tong(long n, long x){
    double s=1, gt=1;
    for(int i=1; i<=n;i++){
        gt*=x;
        s+=gt*1.0/i;
    }
    return s;
}