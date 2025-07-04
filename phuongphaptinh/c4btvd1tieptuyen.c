#include<stdio.h>
#include<math.h>

#define epsilon 1e-6

double f(int n, double x){
    switch(n){
        case 1: return pow(x,3) + x*x - 2*x - 5;
        case 2: return pow(x,4) - 3*x*x + 75*x -1000;
        case 3: return pow(x,3) + 3*x*x - 5*x - 7;
        case 4: return pow(x,5) - 7*pow(x,3) + 6*x*x +15*x - 79;
        case 5: return pow(x, 3) - 7*pow(x, 2) + 14*pow(x, 1) - 8*pow(x, 0);
        default: printf(" chon n khong hop le....");
        return 0;
    }
}
double fdh(int n, double x){
    switch(n){
        case 1: return 3*x*x + 2*x -2;
        case 2: return pow(x,3)*4 - 6*x + 75;
        case 3: return 3*x*x + 6*x - 5;
        case 4: return 5*pow(x,4) - 21*x*x + 12*x + 15;
        case 5: return 3*pow(x,2) - 14*pow(x,1) + 14*pow(x, 0);
        default : printf(" chon n khong hop le....\n");
        return 0;
    }
}   


int main(){
    int n;
    printf("chon phuong trinh (1,2,3,4): ");
    scanf("%d",&n);
    if(n<=0 || n>5){
        printf("chon khong thanh cong....\n");
        return 1;
    }
    double y,x;
    printf("nhap x= ");
    scanf("%lf",&x);
    y = -9999;
    
    while(fabs(x - y) >epsilon){
        y=x;
        x = y - f(n,y)/fdh(n,y);
        printf("%lf         %lf\n",y,f(n,y)/fdh(n,y) );
    }
    printf("ngiem la: %lf\n",x);
    
}