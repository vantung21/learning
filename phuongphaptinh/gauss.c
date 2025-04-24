#include<stdio.h>

#define max 101

void nhap(double a[][max], int n){
    for(int i=0; i<n; i++){
        for(int j=0; j<=n; j++){
            scanf("%lf",&a[i][j]);
        }
    }
}

void gauss(double a[][max], int n){

    // chuyen ma tran a thanh matran duong cheo a'
    for(int i=0; i<n-1; i++){
        if(a[i][i] == 0){
            int dong = n;
            for(int j = i+1; j<n; j++){
                if(a[j][i]>0){
                    dong = j; break;
                }
            }
            if(dong < n){
                for(int j = 0; j<n; j++){
                    double t = a[i][j];
                    a[i][j] = a[dong][j];
                    a[dong][j] = t;
                }
            }
            else{
                printf("du lieu khong hop le!!\n");
                return;
            }
        }
        for(int j=i+1; j<n; j++){
            double m = -a[j][i]/a[i][i];
            for(int k=i; k<n+1; k++){ //vi a co n+1 cot
                a[j][k] = a[j][k] + m*a[i][k];
            }
        }
    }

    // tim nghiem theo qua trinh nguoc
    double x[max];
    for(int i=n-1; i>=0; i--){
        double s = 0;
        for(int j = i+1; j<n; j++){
            s+=a[i][j]*x[j];
        }
        x[i] = (a[i][n] - s)/a[i][i];
    }
    printf("he co nghiem la:\n");
    for(int i=0; i<n; i++){
        printf("x[%d] = %.3lf\n",i,x[i]);
    }
}

int main(){
    int n;double x[max];
    printf("nhap n: "); scanf("%d",&n);

    double a[max][max];
    nhap(a,n);
    gauss(a,n);

    return 0;
}