#include <stdio.h>
#include <math.h>

int main(){
    double a[100], p, c;
    int n;
    printf("nhap bac cua da thuc: ");
    scanf("%d",&n);
    printf("nhap cac he so cua da thuc:\n");
    for(int i=0; i<=n; i++){
        printf("a[%d] = ",i);
        scanf("%lf",&a[i]);
    }
    p = a[0];
    printf("xac dinh da thuc p(y+c), voi c = ");
    scanf("%lf",&c);
    for(int i=0; i<n; i++){
        for(int j=1; j<=n-i; j++){
            p=p*c+a[j];
            a[j]=p;
        }
        p=a[0];
    }
    printf("p(y + %.0lf) = ",c);
    for(int i=0; i<=n-1; i++){
        printf("%.0lf*X^%d + ",a[i],n-i);
    }
    printf("%.0lf",a[n]);
}