#include<stdio.h>
#include<math.h>

#define epsilon 1e-6

double f(int n, double x){
    switch(n){
        case 1: return pow(x,3) + x*x - 2*x - 5;
        case 2: return pow(x,4) - 3*x*x + 75*x -1000;
        case 3: return pow(x,3) + 3*x*x - 5*x - 7;
        case 4: return pow(x,5) - 7*pow(x,3) + 6*x*x +15*x - 79;
        default: printf(" chon n khong hop le....");
        return 0;
    }
}

int main(){
    int n;
    printf("chon phuong trinh (1,2,3,4): ");
    scanf("%d",&n);
    if(n<=0 || n>4){
        printf("chon khong thanh cong....\n");
        return 1;
    }

    double a,b, x=0;
    printf("nhap khoang nghiem a,b voi f(a)*f(b)<0\n");
    printf("a = ");
    scanf("%lf",&a);
    printf("b = ");
    scanf("%lf",&b);
    if(f(n,a)*f(n,b)>0){
        printf("a,b khong hop le!!");
        return 1;
    }

    printf("a\t\tb\t\tx\t\tf(x)\n");
    while(fabs(f(n,x))>epsilon){
        x = a - ((b-a)*f(n,a))/(f(n,b)-f(n,a));
        printf("%lf\t%lf\t%lf\t%lf\n",a,b,x,f(n,x));
        if(f(n,x)*f(n,a)<0){
            b = x;
        }
        else a = x;
    }
    printf("nghiem theo pp day cung la: %lf\n",x);

}