#include <stdio.h>
#include <limits.h>
#define MAX 100

int n; // So dinh
int graph[MAX][MAX]; // Ma tran trong so

// Tim dinh co gia tri nho nhat chua co trong MST
int minKey(int key[], int mstSet[]) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < n; v++) {
        if (mstSet[v] == 0 && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

// Thuat toan Prim
void primMST() {
    int parent[MAX]; // Mang luu cay khung
    int key[MAX];    // Gia tri nho nhat de chon canh
    int mstSet[MAX]; // Mang danh dau dinh da thuoc MST

    // Khoi tao gia tri ban dau
    for (int i = 0; i < n; i++) {
        key[i] = INT_MAX;
        mstSet[i] = 0;
    }

    key[0] = 0;     // Chon dinh dau tien
    parent[0] = -1; // Dinh goc cua MST

    for (int count = 0; count < n - 1; count++) {
        int u = minKey(key, mstSet);
        mstSet[u] = 1;

        for (int v = 0; v < n; v++) {
            if (graph[u][v] && mstSet[v] == 0 && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    // In ket qua
    int d=0;
    printf("Cac canh trong cay khung nho nhat:\n");
    for (int i = 1; i < n; i++) {
        printf("(%d - %d) trong so %d\n", parent[i], i, graph[i][parent[i]]);
        d += graph[i][parent[i]];
    }
    printf("tong trong so cua cay khung be nhat la: %d\n",d);
}

int main() {
    printf("Nhap so dinh: ");
    scanf("%d", &n);

    printf("Nhap ma tran trong so:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    primMST();
    return 0;
}
