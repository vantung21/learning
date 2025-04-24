#include<stdio.h>

int det(int a[][101], int n){
    if(n == 1) return a[0][0];
    if(n == 2) return a[0][0]*a[1][1] - a[0][1]*a[1][0];
    int Det = 0;

    //khai trien theo hang dau tien
    for(int f = 0; f<n; f++){
        int childA[101][101];   // luu mang con sau khi bo hang 1 cot j
        int p = 0, q = 0;
        for(int i = 1; i<n; i++){
            for(int j=0; j<n; j++){
                if(j != f){
                    childA[p][q++] = a[i][j];
                    if( q == n-1){
                        q=0; p++;
                    }
                }
            }
        }
        Det += (f%2==0?1:-1)*a[0][f]*det(childA, n-1);
    }
    return Det;
}

void nhap(int a[][101], int n){
    for(int i=0; i<n; i++){
        for(int j=0; j<=n; j++){
            scanf("%d",&a[i][j]);
        }
    }
}

int main(){
    int n; 
    printf("nhap n: "); scanf("%d",&n);
    int a[101][101];
    printf("nhap cac he so: \n");
    nhap(a,n);
    int M[101][101], P[n],Di[n];

    for(int i=0; i<n; i++){
        P[i]=a[i][n];
    }

    for(int i=0; i<n; i++){
        for(int j=0;j<n; j++){
            M[i][j] = a[i][j];
        }
    }
    int D = det(M,n);
    if(D == 0){
        printf("he vo so nghiem!!!");
        return 1;
    }
    for(int k=0; k<n; k++){
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                M[i][j] = a[i][j];                
            }
        }
        for(int i=0; i<n; i++){
            M[i][k] = P[i];
        }
        Di[k] = det(M,n);
    }

    double x[n];
    for(int i=0; i<n; i++){
        x[i] = 1.0*Di[i]/D;
    }
    for(int i=0; i<n; i++){
        printf("X%d = %lf\n",i+1,x[i]);
    }
}