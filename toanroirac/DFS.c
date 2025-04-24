#include <stdio.h>
#include <stdbool.h>

#define MAX_NODES 100

void DFS(int adjList[][MAX_NODES], int node, bool visited[], int n) {
    visited[node] = true;
    printf("%d ", node);

    for (int i = 0; i < n; i++) {
        if (adjList[node][i] == 1 && !visited[i]) {
            DFS(adjList, i, visited, n);
        }
    }
}

int main() {
    int adjList[MAX_NODES][MAX_NODES] = {0};
    int n, e;
    printf("Nhap so dinh va so canh: ");
    scanf("%d %d", &n, &e);

    printf("Nhap cac canh (u v):\n");
    for (int i = 0; i < e; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adjList[u][v] = 1;
        adjList[v][u] = 1;
    }

    int start;
    printf("Nhap dinh bat dau: ");
    scanf("%d", &start);

    bool visited[MAX_NODES] = {false};
    printf("DFS: ");
    DFS(adjList, start, visited, n);
    printf("\n");

    return 0;
}