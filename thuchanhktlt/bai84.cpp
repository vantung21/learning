#include <stdio.h>

void nhap(long long A[100][100], int *n);
void xuat(long long A[100][100], int n);
long long det(long long A[100][100], int n);

int main(){
	int n;
	long long A[100][100];
	nhap(A,&n);
	xuat(A,n);
	printf("Dinh thuc cua ma tran A la : %lld",det(A,n));
}

void nhap(long long A[100][100], int *n){
	printf("Nhap kich thuoc cua ma tran A : ");
	scanf("%d", n);
	printf("Nhap ma tran A :\n");
	for (int i = 0; i < *n; i++){
		for (int j = 0; j < *n; j++){
			scanf("%lld", &A[i][j]);
		}
	}
}

void xuat(long long A[100][100], int n){
	printf("Ma tran A :\n");
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			printf("%lld\t", A[i][j]);
		}
		printf("\n");
	}
}

long long det(long long A[100][100], int n){
	if (n == 1) return A[0][0];
	if (n == 2) return A[0][0]*A[1][1] - A[0][1]*A[1][0];
	long long s = 0;
	for (int j = 0; j < n; j++){
		long long sub_A[100][100];
		for (int x = 1; x < n; x++){
			int cot = 0;
			for (int y = 0; y< n; y++){
				if (y == j) continue;
				sub_A[x - 1][cot] = A[x][y];
				cot ++;
			}
		}
		s += (j % 2 == 0? 1 : -1)*A[0][j]*det(sub_A,n-1);
	}
	return s;
}
