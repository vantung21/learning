#include<stdio.h>
#include<math.h>

#define epsilon 1e-6

double f(double x){
    return pow(x,3) + x*x - 2*x - 5;
}


int main(){
    double a,b,c;

    printf("nhap f(a), f(b) voi f(a)*f(b)<0\n");
    printf("a = ");
    scanf("%lf",&a);
    printf("b = ");
    scanf("%lf",&b);
    if(f(a)*f(b)>0){
        printf("a,b khong hop le!!");
        return 1;
    }
   
    c=(a+b)/2;
    printf("    a      |     b      |     f((a+b)/2)\n");
    printf("___________|____________|___________\n");
    while(fabs(a-b)>epsilon && f(c)!=0){
        c = (a+b)/2;
        printf("%lf   |  %lf  |   %lf\n",a,b,f(c));
        if(f(c)*f(a)>0) a=c;
        else b=c;
    }

    printf("nghiem gan dung theo phuong phap chia doi la:  %lf\n",c);

    return 0;
}