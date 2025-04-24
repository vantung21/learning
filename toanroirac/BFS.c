#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NODES 100

typedef struct {
    int items[MAX_NODES];
    int front;
    int rear;
} Queue;

Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = -1;
    q->rear = -1;
    return q;
}

bool isEmpty(Queue* q) {
    return q->rear == -1;
}

void enqueue(Queue* q, int value) {
    if (q->rear == MAX_NODES - 1) {
        printf("Queue day!\n");
    } else {
        if (q->front == -1) {
            q->front = 0;
        }
        q->rear++;
        q->items[q->rear] = value;
    }
}

int dequeue(Queue* q) {
    int item;
    if (isEmpty(q)) {
        printf("Queue rong!\n");
        item = -1;
    } else {
        item = q->items[q->front];
        q->front++;
        if (q->front > q->rear) {
            q->front = q->rear = -1;
        }
    }
    return item;
}

void BFS(int adjList[][MAX_NODES], int start, int n) {
    bool visited[MAX_NODES] = {false};
    Queue* q = createQueue();

    visited[start] = true;
    enqueue(q, start);

    printf("BFS: ");
    while (!isEmpty(q)) {
        int current = dequeue(q);
        printf("%d ", current);

        for (int i = 0; i < n; i++) {
            if (adjList[current][i] == 1 && !visited[i]) {
                visited[i] = true;
                enqueue(q, i);
            }
        }
    }
    printf("\n");
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

    BFS(adjList, start, n);

    return 0;
}