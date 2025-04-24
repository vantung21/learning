#include <stdio.h>
#include <math.h>
double dathuc(double x, double n, double a[]){
    double p;
    p = a[0];
    for(int i=1; i<=n; i++){
        p=p*x+a[i];
    }
    return p;
}
int main(){
    double x, n, a[100];
    printf("nhap bac cua da thuc: ");
    scanf("%lf",&n);
    printf("nhap cac he so:\n ");
    for(int i=0; i<=n; i++){
        printf("a[%d] = ",i);
        scanf("%lf",&a[i]);
    }
    printf("nhap x = ");
    scanf("%lf",&x);
    printf("p(x) = %.4lf",dathuc(x,n,a));
}