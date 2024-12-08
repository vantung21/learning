#include<stdio.h>
void nhapmtr(long A[100][100],int m, int n);
void xuatmtr(long A[100][100], int m,int n);
void tonglon(long A[100][100], int m,int n);
int main(){
    int m,n;
    printf("nhap so hang m = ");
    scanf("%d",&m);
    printf("nhap so cot n = ");
    scanf("%d",&n);
    long A[100][100];
    nhapmtr( A,m, n);
    printf("matran A: \n");
    xuatmtr(A,m, n);
    printf("matran A sao khi thay doi: \n");
    tonglon(A,m,n);
}
void nhapmtr(long A[100][100], int m,int n){
    printf("nhap matran A: \n");
    for (int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            scanf("%ld",&A[i][j]);
        }
    }
}
void xuatmtr(long A[100][100],int m, int n){
   
    for (int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            printf("%ld ",A[i][j]);
        }
        printf("\n");
    }
}
void tonglon(long A[100][100],int m, int n){
    long s=0;
    for( int i=0; i<m; i++){
        long max=A[i][0],b=0;
        for(int j=1; j<n; j++){
            if(A[i][j]>max){
                max=A[i][j];
                b=j;
            }
        }
        s+=max;
        if(i>n){
            A[i][b]=A[i][n];
            A[i][n]=max;
        }
        A[i][b]=A[i][i];
        A[i][i]=max;
    }
     xuatmtr(A,m,n);
        printf("tong cac phan tu lon nhat moi hang la: %ld",s);
}
