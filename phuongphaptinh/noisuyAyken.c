#include <stdio.h>

double ayken(double x[], double y[], int n, double c){
    double wc = 1;
    double result = 0;
    for(int i = 0; i<=n; i++){
        wc *= (c - x[i]);
    }
    for(int i=0; i<=n; i++){
        double di = c-x[i];
        for(int j = 0; j <= n; j++){
            if(i != j){
                di *=  (x[i] - x[j]);
            }
        }
        result += wc * y[i]/di;
    }
    return result;
}

int main(){
    double x[100], y[100], c;
    int n;
    printf("Nhap n: ");
    scanf("%d",&n);
    for(int i = 0; i<=n; i++){
        printf("x[%d], y[%d]: ", i, i);
        scanf("%lf%lf", &x[i], &y[i]);
    }

    printf("tinh f(c) voi c = ");
    scanf("%lf", &c);

    double result = ayken(x, y, n, c);
    printf("f(%.2lf) = %.4lf\n", c, result);
    return 0;
}