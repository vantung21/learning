#include<stdio.h>
#include<math.h>

#define maxn 20
#define epsilon 1e-6
double a[maxn][maxn],b[maxn][maxn], M[maxn][maxn], M1[maxn][maxn], c[maxn][maxn], coeff[maxn], coeffDH[maxn], nghiem[maxn];
int songhiem;
void mult(int n, double x[][maxn], double y[][maxn], double z[][maxn]){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            z[i][j] = 0;
            for(int k = 0; k<n; k++){
                z[i][j] += x[i][k]*y[k][j];
            }
        }
    }
}

double f(double x, int n){
    double s = 0;
    for(int i = 0 ; i<=n; i++){
        s += coeff[i]*pow(x, i);
    }
    return s;
}   
double fdh(double x, int n){
    double s = 0;
    for(int i = 0 ; i<n; i++){
        s += coeffDH[i]*pow(x, i);
    }
    return s;   
}

void daoham(int n){
    for(int i = 0; i<n; i++){
        coeffDH[i] = coeff[i+1]*(i+1);
    }
}

double giaipt(double x, int n) {
    double y = x+1;
    int iter = 0;
    while (fabs(x-y) > epsilon && iter < 1000) {
        y = x;
        double f_val = f(y, n);
        double fdh_val = fdh(y, n);
        if (fabs(fdh_val) < epsilon) {
            x += 0.1;  
            continue;
        }
        x = y - f_val / fdh_val;
        iter++;
    }
    return x;
}

void tinhsonghiem(int n){
    songhiem = 0;
    double start = 20;
    double end = -20;
    double step = -0.1;
    double x = start;
    while(x >= end && songhiem < n){
        double root = giaipt(x,n);
        int check = 1;
        for(int i = 0; i<songhiem; i++){
            if(fabs(root - nghiem[i])< epsilon) check = 0;
        }
        if(check) nghiem[songhiem++] = root;
        x += step;
    }
}


void printPolynomial(int n) {
    printf("P(x) = ");
    for (int i = n; i >= 0; i--) {
        if (i == n) printf("%.2fx^%d", coeff[i], i);
        else {
            if (coeff[i] >= 0) printf(" + %.2fx^%d", coeff[i], i);
            else printf(" - %.2fx^%d", -coeff[i], i);
        }
    }
    printf("\n");
}

void printfdh(int n) {
    printf("fdh(x) = ");
    for (int i = n-1; i >= 0; i--) {
        if (i == n-1) printf("%.2fx^%d", coeffDH[i], i);
        else {
            if (coeffDH[i] >= 0) printf(" + %.2fx^%d", coeffDH[i], i);
            else printf(" - %.2fx^%d", -coeffDH[i], i);
        }
    }
    printf("\n");
}
int main(){
    int n;
    printf("nhap kich thuoc ma tran: ");
    scanf("%d",&n);
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(i==j) c[i][j] = 1;
            else c[i][j] = 0;
        }
    }
    printf("nhap ma tran a:\n");
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            scanf("%lf", &a[i][j]);
        }
    }

    for(int k = n-2; k >= 0; k--){
        for(int i=0; i<n; i++){
            for(int j = 0; j<n; j++){
                if(i != k){
                    if(i == j){
                        M[i][j] = 1; M1[i][j] = 1;
                    }
                    else {
                        M[i][j] = 0; M1[i][j] = 0;
                    }
                }
                else{
                    M1[i][j] = a[k+1][j];
                    if(j == k) M[i][j] = 1/a[k+1][k];
                    else M[i][j] = -1*a[k+1][j]/a[k+1][k];
                }
            }
        }
        mult(n, a, M, b);
        mult(n, M1, b, a);
        mult(n, c, M, b);
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                c[i][j] = b[i][j];
            }
        }
    }
    printf("ma tran P la:\n");
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            printf("%8.3lf ", a[i][j]);
        }
        printf("\n");
    }

    for(int i=0; i<n; i++){
        coeff[i] = -a[0][n-i-1];
    }
    coeff[n] = 1;
    daoham(n);
    tinhsonghiem(n);
    printPolynomial(n);
    printfdh(n);
    printf("matran co %d gia tri rieng:\n",songhiem);
    for(int i = 0; i < songhiem; i++){
        printf("%8.3lf", nghiem[i]);
    }
    printf("\n");
    double X[maxn][maxn], Y[maxn][maxn];
    printf("vecto rieng cua matran P la:\n");
    for(int i=0; i<songhiem; i++){
        printf("tri rieng = %.3lf : \t y%d = (  ",nghiem[i], i+1);
        for(int j = 1; j<=n; j++){
            printf("%.3lf  ", pow(nghiem[i],n-j));
            Y[i][j-1] = pow(nghiem[i],n-j);
        }
        printf(")\n");
    }

    //nhan matran c voi y => x
    printf("vecto rieng cua matran A la:\n");
    for(int i=0; i<songhiem; i++){
        for(int j = 0; j<n; j++){
            X[i][j] = 0;
            for(int k = 0; k<n ; k++){
                X[i][j] += c[j][k]*Y[i][k];
            }
        }
        printf("x%d = ( ", i+1);
        for(int m = 0; m<n; m++){
            printf("%.3lf ", X[i][m]);
        }
        printf(" )\n");
    }
    return 0;
}
