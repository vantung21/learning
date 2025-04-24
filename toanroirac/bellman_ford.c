#include <stdio.h>
#include <stdlib.h>

#define INF 1000000
#define MAX_EDGES 100
#define MAX_VERTICES 100

// Cau truc canh
typedef struct {
    int u, v;
    int weight;
} Edge;

Edge edges[MAX_EDGES];
int distance[MAX_VERTICES];
int predecessor[MAX_VERTICES];
int V, E;

void bellmanFord(int start) {
    // Khoi tao khoang cach ban dau
    for (int i = 1; i <= V; i++) {
        distance[i] = INF;
        predecessor[i] = -1;
    }
    distance[start] = 0;

    // Lap V-1 lan de cap nhat khoang cach
    for (int i = 1; i <= V - 1; i++) {
        for (int j = 1; j <= E; j++) {
            int u = edges[j].u;
            int v = edges[j].v;
            int w = edges[j].weight;

            if (distance[u] != INF && distance[u] + w < distance[v]) {
                distance[v] = distance[u] + w;
                predecessor[v] = u;
            }
        }
    }

    // Kiem tra chu trinh am
    for (int j = 0; j < E; j++) {
        int u = edges[j].u;
        int v = edges[j].v;
        int w = edges[j].weight;

        if (distance[u] != INF && distance[u] + w < distance[v]) {
            printf("Do thi co chu trinh am!\n");
            return;
        }
    }

    // In ket qua
    printf("Khoang cach tu dinh %d:\n", start);
    for (int i = 1; i <= V; i++) {
        printf("Den %d: %d\n", i, distance[i]);
    }
}

int main() {
    printf("Nhap so dinh va so canh: ");
    scanf("%d %d", &V, &E);

    printf("Nhap cac canh theo dinh dang: u v weight\n");
    for (int i = 1; i <= E; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].weight);
    }

    int start;
    printf("Nhap dinh bat dau: ");
    scanf("%d", &start);

    bellmanFord(start);

    return 0;
}
