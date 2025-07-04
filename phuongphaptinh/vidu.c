#include<stdio.h>
#include<math.h>

#define epsilon 1e-6
double f(double x){
    return pow(x, 3) - 7*pow(x, 2) + 14*pow(x, 1) - 8*pow(x, 0);
}
double fdh(double x){
    return 3*pow(x,2) - 14*pow(x,1) + 14*pow(x, 0);
}

int main(){
    double x,y;
    scanf("%lf", &x);
    y = -9999;
    
    while(fabs(x - y) >epsilon){
        y=x;
        x = y - f(y)/fdh(y);
        printf("%lf         %lf\n",y,f(y)/fdh(y) );
    }
    printf("ngiem la: %lf\n",x);
    return 0;
}