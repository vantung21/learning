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
    for(int i=0; i<n; i++){
        y[i] = x[i];
    }
    int t = 1;
    int cnt = 0;

    printf("\t\t");
    for(int i=0; i<n; i++){
        printf("X(%d)\t\t",i);
    }
    printf("\n");

    while(t){
        t = 0;  cnt++;

        for(int i=0; i<n; i++){
            double s=0;
            for(int j=0; j<n; j++){
                if(i != j){
                    s += a[i][j]*y[j];
                }
            }
            y[i] = (a[i][n] - s)/a[i][i];

            if(fabs(y[i] - x[i]) >= epsilon) t=1;
        } 
        for(int i=0; i<n; i++){
            x[i] = y[i];
        }
        
        printf("%d: \t\t",cnt);
        for(int i=0; i<n; i++){
            printf("%lf\t",x[i]);
        }      
        printf("\n");
    } 
    printf("nghiem cua he phuong trinh la:\n");
    for(int i=0; i<n; i++){
        printf("X[%i] = %lf\n",i, x[i]);
    }

}