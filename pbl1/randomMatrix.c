#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_WEIGHT 10 // Giá trị trọng số tối đa
#define SPARSITY 0.3 // xac suat tao canh giua 2 dinh

void generateWeightedMatrix(int n, int matrix[][1001]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j  && ((rand() / (double)RAND_MAX) < SPARSITY)) {
                matrix[i][j] = rand() % (MAX_WEIGHT + 1); // Trọng số từ 0 đến MAX_WEIGHT
            } else {
                matrix[i][j] = 0; // Không có cạnh từ một đỉnh đến chính nó
            }
        }
    }
}

void printMatrix(int n, int matrix[][1001]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%3d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    freopen("inp.txt","r", stdin);
    freopen("outp.txt", "w", stdout);
    int n;
    //printf("Nhập số đỉnh của đồ thị: ");
    scanf("%d", &n);
    
    int matrix[1001][1001];
    srand(time(NULL));
    generateWeightedMatrix(n, matrix);
    
    //printf("\nMa trận trọng số có hướng:\n");
    printMatrix(n, matrix);
    
    return 0;
}
