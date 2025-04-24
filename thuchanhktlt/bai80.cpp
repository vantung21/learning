#include<stdio.h>

void nhapmtr(long A[100][100], int n);
void xuatmtr(long A[100][100], int n);
void tonglon(long A[100][100], int n);

int main(){
    int n;
    printf("Nhap kich thuoc ma tran: ");
    scanf("%d",&n);
    long A[100][100];
    nhapmtr( A, n);
    printf("Ma tran A:\n");
    xuatmtr(A, n);
    printf("Ma tran A sao khi thay doi:\n");
    tonglon(A, n);
}

void nhapmtr(long A[100][100], int n){
    printf("Nhap ma tran A: \n");
    for (int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            scanf("%ld", &A[i][j]);
        }
    }
}

void xuatmtr(long A[100][100], int n){
    for (int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%ld\t", A[i][j]);
        }
        printf("\n");
    }
}

void tonglon(long A[100][100], int n){
    long s = 0;
    for( int i = 0; i < n; i++){
        long max = A[i][0], b = 0;
        for(int j = 1; j < n; j++){
            if(A[i][j] > max){
                max = A[i][j];
                b = j;
            }
        }
        s += max;
        A[i][b] = A[i][n-i-1];
        A[i][n-i-1] = max;
    }
    xuatmtr(A, n);
    printf("Tong cac phan tu lon nhat moi hang la: %ld", s);
}
