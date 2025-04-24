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

    double a,b,c;

    printf("nhap f(a), f(b) voi f(a)*f(b)<0\n");
    printf("a = ");
    scanf("%lf",&a);
    printf("b = ");
    scanf("%lf",&b);
    if(f(n,a)*f(n,b)>0){
        printf("a,b khong hop le!!");
        return 1;
    }
   
    c=(a+b)/2;
    printf("    a      |     b      |     f((a+b)/2)\n");
    printf("___________|____________|___________\n");
    while(fabs(a-b)>epsilon && f(n,c)!=0){
        c = (a+b)/2;
        printf("%lf   |  %lf  |   %lf\n",a,b,f(n,c));
        if(f(n,c)*f(n,a)>0) a=c;
        else b=c;
    }

    printf("nghiem gan dung theo phuong phap chia doi la:  %lf\n",c);

    return 0;
}