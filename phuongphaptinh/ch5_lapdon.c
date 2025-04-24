#include<stdio.h>
#include<math.h>

#define max 101
#define epsilon 1e-6

void nhap(double a[][max], int n,double x[]){
    for(int i=0; i<n; i++){
        for(int j=0; j<=n; j++){
            scanf("%lf",&a[i][j]);
        }
    }

    for(int i=0; i<n; i++){
        scanf("%lf", &x[i]);
    }
}


int main(){
    int n; printf("nhap n: "); scanf("%d",&n);
    double a[max][max], x[max],y[max];

    nhap(a,n,x);
    int t = 1;

    while(t){
        t = 0;

        for(int i=0; i<n; i++){
            double s=0;
            for(int j=0; j<n; j++){
                if(i != j){
                    s += a[i][j]*x[j];
                }
            }
            y[i] = (a[i][n] - s)/a[i][i];

            if(fabs(y[i] - x[i]) >= epsilon) t=1;
        } 
        for(int i=0; i<n; i++){
            x[i] = y[i];
        }
        printf("%lf\t%lf\t%lf\n",x[0],x[1],x[2]);       
    } 
    printf("nghiem cua he phuong trinh la:\n");
    for(int i=0; i<n; i++){
        printf("X[%i] = %lf\n",i, x[i]);
    }

}