#include<stdio.h>
int main(){
    double a,b,s,i=0;
    scanf("%lf%lf",&a,&b);
    s=a;
    while(s<b){
        s=s+s*0.011;
        i++;
    }
    printf("%.0lf",i);

}