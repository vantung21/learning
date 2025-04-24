#include<stdio.h>
#include<math.h>
#define epsilon 1e-6

double g(int n,double x){
    switch(n){
        case 1: return  pow(-x*x + 2*x + 5, 1.0/3);
        case 2: return pow(3*x*x -75*x + 1000, 1.0/4);
        case 3: return pow(-3*x*x + 5*x +7, 1.0/3);
        case 4: return pow(pow(x,3)*7 - 6*x*x - 15*x + 79, 1.0/5);
        default: printf("chon n khong hop le....\n");
        return 0;
    }
    return pow(-x*x + 2*x + 5, 1.0/3);
}

int main(){
    int n;
    printf("chon phuong trinh (1,2,3,4): ");
    scanf("%d",&n);

    double x,y;
    printf("nhap x = "); scanf("%lf",&x);
    printf("    x      |     g(x)\n");
    printf("___________|_____________\n");
    y=x; x=g(n,y);
    printf("%lf   |  %lf\n",y, x);
    while(fabs(x-y)>epsilon){
       y=x;
       x = g(n, y);
       printf("%lf   |  %lf\n",y, x);
    }

    printf("nghiem gan dung theo phuong phap lap la: %lf\n",x);
}