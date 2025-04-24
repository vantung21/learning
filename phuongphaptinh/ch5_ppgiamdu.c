#include<stdio.h>
#include<math.h>

#define maxn 101
#define epsilon 1e-3
void nhap(double a[][maxn], int n,double x[]){
    for(int i=0; i<n; i++){
        for(int j=0; j<=n; j++){
            scanf("%lf",&a[i][j]);
        }
    }

    for(int i=0; i<n; i++){
        scanf("%lf", &x[i]);
    }
}

// void checkdk(double a[][maxn], int n){
//     for(int i = 0; i<n; i++){
//         if(a[i][i] == 0)
//     }
// }

int main(){
    int n; printf("nhap n: "); scanf("%d",&n);
    double a[maxn][maxn], x[maxn],y[maxn], r[maxn];
    nhap(a,n,x);
    for(int i=0; i<n; i++){
        y[i] = x[i];
    }

    //chuyen he ptr ve dang 2
    for(int i=0; i<n; i++){
        double t = a[i][i];
        for(int j=0; j<= n; j++){
            a[i][j] = a[i][j]/t;
        }
    }

    // tinh gia ttri dau cho r[i]
    for(int i=0; i<n; i++){
        r[i] = a[i][n];
        for(int j=0; j<n; j++){
            r[i] -= a[i][j]*x[j];
        }
    }

    // in bang gia tri
    for(int i=0; i<n; i++){
        printf("%.3lf\t\t",x[i]);
    }
    for(int i=0; i<n; i++){
        printf("%.3lf\t\t",r[i]);
    }
    printf("\n");

    int stop = 1;
    while(stop){

        
        stop = 0;
        double max = fabs(r[0]) ; int k = 0;
        for(int i=1; i<n; i++){
            if(max < fabs(r[i])){
                max = r[i];
                k = i;
            }
        }
        x[k] = x[k] + r[k];

        //tinh lai r[i] kiem tra kha nang lap tiep theo
        double d = r[k];
        for(int i=0; i<n; i++){
            r[i] = r[i] - a[i][k]*d;
            if(r[i]>= epsilon) stop = 1;
        }

        // in bang gia tri
        for(int i=0; i<n; i++){
            if(y[i] == x[i]){
                printf("\t\t"); continue;
            }
            printf("%.3lf\t\t",x[i]);
        }
        for(int i=0; i<n; i++){
            printf("%.3lf\t\t",r[i]);
        }
        printf("\n");

        for(int i=0; i<n; i++){
            y[i] = x[i];
        }
    }
    printf("nghiem cua he phuong trinh la:\n");
    for(int i=0; i<n; i++){
        printf("X[%i] = %.3lf\n",i, x[i]);
    }
    
}