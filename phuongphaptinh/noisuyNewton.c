#include <stdio.h>

double newton(double x[], double y[][100], int n, double c){
    double h = x[1] - x[0];
    for(int i = 1; i<=n; i++){
        for(int j = i; j<=n; j++){
            y[j][i] = y[j][i-1] - y[j-1][i-1];
        }
    }

    double result = y[0][0];
    for(int i=1; i<=n; i++){
        double tmp = y[i][i];
        for(int j = 1; j<=i; j++){
            tmp *= (c - x[j-1])/(h*j) ;
        }
        result += tmp;
    }
    return result;

}

int main(){
    double result, x[100], y[100][100], c;
    int n;
    scanf("%d", &n);
    for(int i=0; i<=n; i++){
        scanf("%lf%lf",&x[i], &y[i][0]);
    }
    scanf("%lf", &c);

    result = newton(x, y, n, c);
    printf("bang sai phan:\n");
    printf("             xi          f(xi)");
    for(int i = 1; i<=n; i++){
        printf("        d%df(xi)", i);
    }
    printf("\n");
    for(int i = 0; i<=n; i++){
        printf("%15.lf", x[i]);
        for(int j = 0 ; j<=i; j++){
            printf("%15.3lf",y[i][j]);
        }
        printf("\n");
    }

    printf("f(%.3lf) = %.3lf\n", c, result);

    return 0;
}