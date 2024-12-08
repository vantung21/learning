#include<stdio.h>
void nhapmtr(long A[100][100], int n);
void xuatmtr(long A[100][100], int n);
long det(long A[100][100], int n);
void mtrdao(long A[100][100],int n);

int main(){
    int n;
    printf("nhap kich thuoc matran: ");
    scanf("%d",&n);
    long A[100][100];
    nhapmtr( A, n);
    xuatmtr(A, n);
    mtrdao(A,n);
   
}
void nhapmtr(long A[100][100], int n){
    printf("nhap matran A: \n");
    for (int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            scanf("%ld",&A[i][j]);
        }
    }
}
void xuatmtr(long A[100][100], int n){
    printf("matran A: \n");
    for (int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            printf("%ld ",A[i][j]);
        }
        printf("\n");
    }
}
long det(long A[100][100], int n){
    if(n==1) return A[0][0];
    if(n==2) return A[0][0]*A[1][1]-A[0][1]*A[1][0];
    long D=0;
    for(int f=0; f<n; f++){
        long a[100][100];
        int p=0, q=0;
        for(int i=1;i<n; i++){
            for(int j=0; j<n;j++){
                if(j!=f){
                    a[p][q++]=A[i][j];
                    if(q==n-1){
                        q=0;
                        p++;
                    }
                }
            }
        }
        D+= (f%2==0?1:-1)*A[0][f]*det(a, n-1);
    }
    return D;
}
void mtrdao(long A[100][100], int n){
    if(det(A, n)==0){
        printf("khong ton tai matran nghich dao cua A");
    }
    else{
        double B[100][100];
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                
                long b[100][100];
                int p=0,q=0;
                
                for(int x=0; x<n;x++){
                    if(x==i) continue;
                    for(int y=0; y<n;y++){
                        if(y==j) continue;
                        b[p][q++]=A[x][y];
                        if(q==n-1){
                            q=0; p++;
                        }
                    }
                }
                B[j][i] = ((i+j)%2==0?1:-1)*det(b, n-1)/(1.0*det(A,n));
            
            }
        }
        printf("matran nghich dao cua A la: \n");
        for(int i=0; i<n; i++){
            for(int j=0; j<n;j++){
                printf("%.2lf ",B[i][j]);
            }
            printf("\n");
        }
    }
}