#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct minHeapNode{
    int vertex;
    int distance;
}minHeapNode;

typedef struct minHeap{
    minHeapNode* node;
    int size;
}minHeap;

void swap(minHeap* m, int i, int j){
    minHeapNode temp = m->node[i];
    m->node[i] = m->node[j];
    m->node[j] = temp;
}

minHeap* createMinHeap(int capacity){
    minHeap* m = (minHeap*)malloc(sizeof(minHeap));
    m->node = (minHeapNode*)malloc(capacity*sizeof(minHeapNode));
    m->size = 0;
    return m;
}

void heapifyUp(minHeap* m, int i){
    while (i > 1 && m->node[i / 2].distance > m->node[i].distance) {
        swap(m, i, i / 2);
        i /= 2;
    }
}

void heapifyDown(minHeap* m, int i){
    while(2 * i <= m->size){
        int leftChild = 2 * i;
        int rightChild = leftChild + 1;
        int smallest = leftChild;
        
        if(rightChild <= m->size && m->node[rightChild].distance < m->node[leftChild].distance){
            smallest = rightChild;
        }
        if(m->node[i].distance <= m->node[smallest].distance) break;
        swap(m, i, smallest);
        i = smallest;
    }
}
void add(minHeap* m, int vertex, int distance){
    m->size++;
    m->node[m->size].vertex = vertex;
    m->node[m->size].distance = distance;
    heapifyUp(m, m->size);
}

minHeapNode poll(minHeap* m){
    minHeapNode root = m->node[1];
    m->node[1] = m->node[m->size];
    m->size--;
    heapifyDown(m, 1);
    return root;
}

//cau truc cua danh sach ke  
typedef struct edge{
    int v, w; 
    struct edge* next;
} *Edge;
void addEdge(Edge adj[], int u, int v, int w){
    Edge e = (Edge)malloc(sizeof(struct edge));
    e->v = v; e->w = w;
    e->next = adj[u];
    adj[u] = e;
}

void dijkstra(int v, Edge adj[], int start, int end){
    int L[v+1], P[v+1], visited[v+1];
    for (int i = 1; i <= v; i++){
        L[i] = INT_MAX; P[i] = 0; visited[i] = 0;
    }
    L[start] = 0;
    minHeap* MH = createMinHeap(100);
    add(MH, start, 0);

    //vong lap chinh
    while (MH->size > 0){
        minHeapNode minNode = poll(MH);
        int u = minNode.vertex;
        int distance = minNode.distance;
        if(visited[u]) continue;
        visited[u] = 1;

        Edge temp = adj[u];
        while(temp != NULL){
            int x = temp->v;
            int w = temp->w;

            if(!visited[x] && L[u] + w < L[x]){
                L[x] = L[u] + w;
                add(MH, x, L[x]);
                P[x] = u;
            }
            temp = temp->next;
        }
    }
    if(L[end] == INT_MAX){
        printf("Khong co duong di tu %d den %d !\n", start, end);
        return;
    }
    printf("Duong di ngan nhat tu (%d) den (%d): %d\n", start, end, L[end]);
    printf("Duong di:\n");
    int path[v], npath = 0;
    int a = end;
    while(a != 0){
        path[npath++] = a;
        a = P[a];
    }
    for(int i = npath-1; i>0; i--){
        printf("%c -> ", path[i]+'A'-1);
    }
    printf("%c\n", path[0]+'A'-1);
}

int main(){
    int v,n;
    printf("nhap so dinh va so canh: "); scanf("%d%d", &v, &n);
    Edge adj[v+1];
    for(int i = 1; i<=v; i++){
        adj[i] = NULL;
    }
    printf("nhap cac canh (v1, v2, w):\n");
    int v1, v2, w;
    for(int i = 1; i<=n; i++){
        scanf("%d%d%d", &v1, &v2, &w);
        addEdge(adj, v1, v2, w);
        addEdge(adj, v2, v1, w);
    }
    int start, end;
    printf("nhap dinh dau va dinh cuoi: "); scanf("%d%d", &start, &end);
    dijkstra(v, adj, start, end);
    return 0;
}