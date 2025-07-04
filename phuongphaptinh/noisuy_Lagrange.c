#include <stdio.h>

double noisuyLagrange(double x[], double y[], int n, double a){
    double result = 0;
    for(int i = 0; i < n; i++){
        double p = y[i];
        for(int j = 0; j < n; j++){
            if(i == j) continue;
            p *= (a-x[j])/(x[i]-x[j]);
        }
        result += p;
    }
    return result;

}

int main(){
    double  x[100], y[100], a;
    int n;
    printf("Nhap n: ");
    scanf("%d", &n);
    printf("Nhap cac cap x ,y :\n");
    for(int i = 0; i<n; i++){
        scanf("%lf%lf", &x[i], &y[i]); 
    }
    printf("tinh f(x) voi x = ");
    scanf("%lf", &a);
    double result = noisuyLagrange(x, y, n, a);
    printf("f(%.2lf) = %.4lf\n", a, result);


    return 0;
}