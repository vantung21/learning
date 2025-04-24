#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Cau truc canh
typedef struct {
    int u, v, weight;
} Edge;

Edge edges[MAX]; // Danh sach canh
int parent[MAX]; // Mang cha cua moi dinh
int n, m; // So dinh va so canh

// Ham so sanh de sap xep cac canh theo trong so tang dan
int compare(const void *a, const void *b) {
    return ((Edge*)a)->weight - ((Edge*)b)->weight;
}

// Tim goc cua tap hop chua dinh u
int find(int u) {
    if (parent[u] == u)
        return u;
    return parent[u] = find(parent[u]); // Path compression
}

// Hop nhat hai tap hop
void unionSet(int u, int v) {
    parent[find(u)] = find(v);
}

// Thuat toan Kruskal
void kruskal() {
    int mst_weight = 0; // Tong trong so cua cay khung nho nhat
    int mst_edges = 0; // So canh da them vao cay khung nho nhat
    
    // Sap xep cac canh theo trong so tang dan
    qsort(edges, m, sizeof(Edge), compare);

    // Khoi tao tap hop cha
    for (int i = 0; i < n; i++)
        parent[i] = i;

    printf("Cac canh trong cay khung nho nhat:\n");

    for (int i = 0; i < m; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].weight;

        // Neu u va v thuoc 2 tap hop khac nhau, them canh vao cay khung
        if (find(u) != find(v)) {
            printf("(%d, %d) - %d\n", u, v, w);
            mst_weight += w;
            unionSet(u, v);
            mst_edges++;

            // Neu so canh du (n - 1) thi dung
            if (mst_edges == n - 1)
                break;
        }
    }

    printf("Tong trong so cua cay khung nho nhat: %d\n", mst_weight);
}

// Chuong trinh chinh
int main() {
    printf("Nhap so dinh va so canh: ");
    scanf("%d %d", &n, &m);

    printf("Nhap danh sach canh (dinh1 dinh2 trong so):\n");
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].weight);
    }

    kruskal();
    return 0;
}
