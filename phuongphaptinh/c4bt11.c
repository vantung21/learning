#include<stdio.h>
#include<math.h>


int main(){
    double a[100],b,N,am;
    int m=1;

    printf("nhap bac cau phuong trinh: ");
    scanf("%lf",&b);

    printf("nhap cac he so: \n");
    for(int i=0; i<=b; i++){
        printf("a[%d] = ",i);
        scanf("%lf",&a[i]);
    }

    if(a[0]<0){
        for(int i=0; i<=b; i++){
            a[i]=-a[i];
        }
    }

    while(1){
        if(a[m]<0){
            break;
        }
        m++; 
    }

    am = fabs(a[m]);

    for(int i=0; i<=b; i++){
        if(a[i]<0 && fabs(a[i])>am){
            am = fabs(a[i]);
        }
    }

    printf("can tren cua nghiem duong: N = %lf\n",1 + pow(am/a[0],1.0/m));
    
    return 0;
}