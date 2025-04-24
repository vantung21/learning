#include<stdio.h>
#include<math.h>
#define epsilon 1e-6

double g(double x){
    return pow(-x*x + 2*x + 5, 1.0/3);
}

int main(){
    double x,y;
    printf("nhap x = "); scanf("%lf",&x);
    printf("    x      |     g(x)\n");
    printf("___________|_____________\n");
    y=x; x=g(y);
    printf("%lf   |  %lf\n",y, x);
    while(fabs(x-y)>epsilon){
       y=x;
       x = g(y);
       printf("%lf   |  %lf\n",y, x);
    }

    printf("nghiem gan dung theo phuong phap lap la: %lf\n",x);
}