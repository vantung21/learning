#include<stdio.h>
double emux(double x, int n){
    double tong =1, a=1;
    for(int i=1; i<n; i++){
        a*=x/i;
        tong +=a;
    }
    return tong;
}
double sinx(double x, int n){
    double tong = x;
    double a=x;
    int dau=-1;
    for(int i=1; i<n; i++){
        a*=x*x/((2*i)*(2*i+1));
        tong +=dau*a;
        dau=-dau;
    }
    return tong;
}
double cosx(double x, int n){
    double tong =1, a=1;
    int dau=-1;
    for(int i=1; i<n; i++){
        a*=x*x/((2*i)*(2*i-1));
        tong +=dau*a;
        dau = -dau;
    }
    return tong;
}
int main(){
    double x;
    int n;
    printf("nhap so luong phan tu trong chuoi maclorin: ");
    scanf("%d",&n);
    printf("nhap x = ");
    scanf("%lf",&x);
    printf("e^x = %lf\n",emux(x,n));
    printf("sin(x) = %lf\n",sinx(x,n));
    printf("cos(x) = %lf",cosx(x,n));

}