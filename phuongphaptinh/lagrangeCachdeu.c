#include <stdio.h>
#include <math.h>


double tohop(int n,  int k){
    double s = 1;
    for(int i = n-k+1; i<=n; i++){
        s*=i;
    }
    for(int i = 2; i<=k; i++){
        s/=i;
    }
    return s;
}

double gt(int x){
    double s =1;
    for(int i = 1; i<=x; i++){
        s*=i;
    }
    return s;
}

double lagrangepro(double x[], double y[], int n, double t){
    for(int i = 0; i <= n; i++){
        if(i == t){
            return y[i];
        }
    }
    double result = t;
    for(int i = 1; i<=n; i++){
        result *= (t-i);
    }
    result /=gt(n);
    double T = 0;
    for(int i = 0; i<= n; i++){
        T += (pow(-1, n-i)*y[i]*tohop(n, i))/(t-i);
    }
    result *=T;
    return result;
}

int main(){
    double x[100], y[100], a;
    int n;
    scanf("%d", &n);
    for(int i=0; i<=n; i++){
        scanf("%lf",&x[i]); scanf("%lf",&y[i]);
    }
    scanf("%lf", &a);
    double h = x[1] - x[0];
    double t = (a - x[0])/h;
    double kq = lagrangepro(x,y,n,t);
    printf("%.3lf\n",kq);

    return 0; 
}