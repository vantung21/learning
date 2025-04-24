#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_WEIGHT 100 // Trọng số tối đa

void generateConnectedMatrix(int n, int** matrix) {
    // Bước 1: Khởi tạo ma trận toàn số 0
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = 0;
        }
    }

    // Bước 2: Sinh cây khung bằng cách nối từng đỉnh i với i+1
    for (int i = 0; i < n - 1; i++) {
        int weight = rand() % MAX_WEIGHT + 1; // Trọng số từ 1 đến MAX_WEIGHT
        matrix[i][i + 1] = weight;
        matrix[i + 1][i] = weight;
    }

    // Bước 3: Thêm một số cạnh ngẫu nhiên để đồ thị phong phú hơn
    int extraEdges = n; // Số cạnh thêm vào (có thể điều chỉnh)
    for (int i = 0; i < extraEdges; i++) {
        int u = rand() % n;
        int v = rand() % n;
        if (u != v && matrix[u][v] == 0) { // Đảm bảo không có cạnh trùng lặp
            int weight = rand() % MAX_WEIGHT + 1;
            matrix[u][v] = weight;
            matrix[v][u] = weight;
        }
    }
}

void printMatrix(int n, int** matrix) {
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
    scanf("%d", &n);
    
    int** matrix = (int**)malloc((n)*sizeof(int*));
    for(int i=0; i<n; i++){
        matrix[i] = (int*)malloc((n)*sizeof(int));
    }

    srand(time(NULL));
    generateConnectedMatrix(n, matrix);
    
    printMatrix(n, matrix);
    
    for(int i=0; i<n; i++){
        free(matrix[i]);
    }
    free(matrix);
    return 0;
}
