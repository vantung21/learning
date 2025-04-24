#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define MAX 100

typedef struct {
    int to;
    int weight;
} Edge;

typedef struct {
    Edge edges[MAX];
    int size;
} AdjList;

AdjList adj[MAX]; // Danh sách kề
int n, m; // số đỉnh, số cạnh

void addEdge(int u, int v, int w) {
    adj[u].edges[adj[u].size].to = v;
    adj[u].edges[adj[u].size].weight = w;
    adj[u].size++;

    adj[v].edges[adj[v].size].to = u;
    adj[v].edges[adj[v].size].weight = w;
    adj[v].size++;
}

int minKey(int key[], bool mstSet[]) {
    int min = INT_MAX, min_index = -1;
    for (int v = 1; v <= n; v++) {
        if (!mstSet[v] && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

void printMST(int parent[], int key[]) {
    int total = 0;
    printf("Cac canh trong cay khung nho nhat:\n");
    for (int i = 1; i <= n; i++) {
        if (parent[i] != -1) {
            printf("(%d, %d) - %d\n", parent[i], i, key[i]);
            total += key[i];
        }
    }
    printf("Tong trong so cua cay khung nho nhat: %d\n", total);
}

void prim() {
    int parent[MAX];
    int key[MAX];
    bool mstSet[MAX];

    for (int i = 1; i <= n; i++) {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    key[1] = 0;       // Bắt đầu từ đỉnh 1
    parent[1] = -1;

    for (int count = 1; count < n; count++) {
        int u = minKey(key, mstSet);
        mstSet[u] = true;

        for (int i = 0; i < adj[u].size; i++) {
            int v = adj[u].edges[i].to;
            int w = adj[u].edges[i].weight;
            if (!mstSet[v] && w < key[v]) {
                key[v] = w;
                parent[v] = u;
            }
        }
    }

    printMST(parent, key);
}

int main() {
    printf("Nhap so dinh va so canh: ");
    scanf("%d %d", &n, &m);

    printf("Nhap cac canh (dinh1 dinh2 trong_so):\n");
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        addEdge(u, v, w);
    }

    prim();
    return 0;
}
