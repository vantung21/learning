#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

int a[1001], s=0;

//cau truc cua danh sach ke
typedef struct edge{
    int v, w;
    struct edge* next;
} *Edge;

void addEdge(Edge *adj, int u, int v, int w){
    Edge e = (Edge)malloc(sizeof(struct edge));
    e->v = v; e->w = w;
    e->next = adj[u];
    adj[u] = e;
}

int count = 0;
void convertMatrixToList(int **graph, Edge *adj, int v){
    for(int i=1; i<=v; i++){
        for(int j=1; j<=v; j++){
            if(graph[i][j] != 0){
                addEdge(adj, i, j, graph[i][j]);
                count++;
            }
        }
    }
}

typedef struct minHeapNode {
    int vertex;          // ten dinh
    int distance;        // khoang cach ngan nhat tu dinh nguon den dinh do
} minHeapNode;

typedef struct minHeap {
    minHeapNode* node;    // mang luu cac phan tu trong minHeap
    int size;             // so dinh trong minHeap
} minHeap;

// doi 2 node trong minHeap
void swap(minHeap* m, int i, int j) {
    minHeapNode temp = m->node[i];
    m->node[i] = m->node[j];
    m->node[j] = temp;
}

minHeap* createMinHeap(int capacity) {
    minHeap* m = (minHeap*)malloc(sizeof(minHeap));
    m->node = (minHeapNode*)malloc((capacity + 1) * sizeof(minHeapNode));
    m->size = 0;
    return m;
}

void heapifyUp(minHeap* m, int i) {
    while (i > 1 && m->node[i / 2].distance > m->node[i].distance) {
        swap(m, i, i / 2);
        i /= 2;
    }
}

void heapifyDown(minHeap* m, int i) {
    while (2 * i <= m->size) {
        int leftChild = 2 * i;
        int rightChild = leftChild + 1;
        int smallest = leftChild;
        
        if (rightChild <= m->size && m->node[rightChild].distance < m->node[leftChild].distance) {
            smallest = rightChild;
        }

        if (m->node[i].distance <= m->node[smallest].distance) break;

        swap(m, i, smallest);
        i = smallest;
    }
}

void add(minHeap* m, int vertex, int distance) {
    m->size++;
    m->node[m->size].vertex = vertex;
    m->node[m->size].distance = distance;
    heapifyUp(m, m->size);
}

minHeapNode poll(minHeap* m) {
    minHeapNode root = m->node[1];
    m->node[1] = m->node[m->size];
    m->size--;
    heapifyDown(m, 1);
    return root;
}

//dijkstra
void dijkstra(int v, Edge *adj, int begin, int end) {
    int *L = (int*)malloc((v+1)*sizeof(int));
    int *P = (int*)malloc((v+1)*sizeof(int));
    int *visited = (int*)malloc((v+1)*sizeof(int));

    if(!L || !P || !visited){
        printf("Loi cap phat bo nho!\n");
        exit(1);
    }

    for (int i = 1; i <= v; i++){
        L[i] = INT_MAX; P[i] = 0; visited[i] = 0;
    }
    L[begin] = 0;

    minHeap* MH = createMinHeap(count);
    add(MH, begin, 0);

    // in dong dau tien cua bang
    for(int i = 1; i <= v; i++){
        printf("(%3d )\t\t\t", i);
    }
    printf("\n");
    for(int i = 1; i <= v; i++){
        printf("________________");
    }    
    printf("\n");

    //vong lap chinh
    while (MH->size > 0) {
        minHeapNode minNode = poll(MH);
        int u = minNode.vertex; visited[u] = 1;
        int distance = minNode.distance;
        if(L[u] < distance) continue;

        //In bang 
        for(int i = 1; i <= v; i++){
            if(L[i] == INT_MAX) printf("(INF,%3d )\t\t", P[i]);
            else printf("(%3d,%3d )\t\t", L[i], P[i]);
        }
        printf("\n");   

        Edge temp = adj[u];
        while(temp != NULL){
            int v = temp->v;
            int w = temp->w;

            if(!visited[v] && L[u] + w <L[v]){
                L[v] = L[u] + w;
                add(MH, v, L[v]);
                P[v] = u;
            }
            temp = temp->next;
        }
    }

    //In duong di ngan nhat
    printf("\nTong trong so cua duong di ngan nhat tu (%d) den (%d) la: %d\n", begin, end, L[end]);
    printf("Duong di:\n");

    int p = end;
    a[s++] = p; 
    while(P[p] != 0){
        a[s++] = P[p];
        p = P[p];
    }

    for(int i = s - 1; i > 0; i--){
        printf("(%d) -> ",a[i]);
    }
    printf("(%d)\n",a[0]);

    free(L); free(P); free(visited);
    free(MH->node);
    free(MH);
}

//tao file ve do thi
void xuatGraphviz(int** graph, int v) {
    FILE* f = fopen("graph.dot", "w");
    if (!f) {
        printf("Lỗi mở file!\n");
        return;
    }

    fprintf(f, "graph G {\n");
   // fprintf(f, "  layout=sfdp;\n");   // Dùng sfdp để vẽ đồ thị tốt hơn với đồ thị lớn
    fprintf(f, "  overlap=scale;\n"); // Tránh chồng lấn, tự động co giãn
    fprintf(f, "  sep=\"+1\";\n");     // Tăng khoảng cách giữa các nhóm đỉnh
    fprintf(f, "  nodesep=1.2;\n");   // Khoảng cách giữa các đỉnh (mặc định là 0.25)
    fprintf(f, "  ranksep=1.5;\n");   // Khoảng cách giữa các tầng
    fprintf(f, "  splines=true;\n");  // Vẽ cạnh mượt hơn, tránh bị gấp khúc
    fprintf(f, "  node [shape=circle, style=filled, fillcolor=lightblue, fontcolor=black, fontsize=10, width=0.8, height=0.8];\n");
    fprintf(f, "  edge [color=blue, penwidth=2, fontcolor=red, fontsize=13];\n");

    //tu them to mau cho cac dinh, canh
    fprintf(f, "  %d [fillcolor=cyan,style=filled,color=red, penwidth=5];\n", a[s-1]);
    fprintf(f, "  %d [fillcolor=cyan,style=filled,color=red, penwidth=5];\n", a[0]);
    for (int i = 1; i <= v; i++) {
        if(i==a[0] || i==a[s-1]) continue;
        int checknode = 0;
        for (int k = 0; k < s; k++) {
            if (a[k] == i) {
                checknode = 1;
                break;
            }
        }
        
        if (checknode)
            fprintf(f, "  %d [fillcolor=cyan, style=filled, penwidth=3];\n", i); // Đỉnh trên đường đi ngắn nhất màu đỏ
        else
            fprintf(f, "  %d [fillcolor=lightblue, style=filled];\n", i); // Đỉnh bình thường màu xanh
    }

    for (int i = 1; i <= v; i++) {
        for (int j = i + 1; j <= v; j++) {
            if (graph[i][j] != 0) {
                //kiem tra xem canh nay co thuoc duong di ngan nhat khong
                int check = 0;
                for(int k=s-1; k>0; k--){
                    if((a[k]==i && a[k-1]==j) || (a[k]==j && a[k-1]==i)){
                        check = 1; break;
                    }
                }
                if(check)
                    fprintf(f, "  %d -- %d [label=\"%d\", color=orange, penwidth = 5];\n", i, j, graph[i][j]);
                else
                    fprintf(f, "  %d -- %d [label=\"%d\", color=black];\n", i, j, graph[i][j]);
            }
        }
    }

    fprintf(f, "}\n");

    fclose(f);
    printf("Xuat thanh cong ra file graph.dot!\n");
} 

int main() {
    freopen("inp.txt", "r", stdin);
    freopen("outp.txt", "w", stdout);
    int v, begin, end;

    scanf("%d", &v);

    // cap phat mang dong 2 chieu
    int** graph = (int**)malloc((v+1)*sizeof(int*));
    if(!graph){
        printf("Loi cap phat bo nho!\n");
        return 1;
    }
    for(int i=0; i<=v; i++){
        graph[i] = (int*)malloc((v+1)*sizeof(int));
        if (!graph[i]) {
            printf("Loi cap phat bo nho!\n");
            return 1;
        }
    }

    //nhap ma tran ke
    for (int i = 1; i <= v; i++){
        for (int j = 1; j <= v; j++)
        scanf("%d", &graph[i][j]);

    }

    scanf("%d%d", &begin, &end);


    Edge *adj = (struct edge**)malloc((v+1)*sizeof(struct edge*));
    if(!adj){
        printf("Loi cap phat bo nho!\n");
        return 1;
    }
    for(int i=0; i<=v; i++){
        adj[i] = NULL;
    }

    convertMatrixToList(graph, adj, v);

    dijkstra(v, adj, begin, end);

    xuatGraphviz(graph, v);

    //giai phong bo nho cap phat dong
    for(int i = 0; i <= v; i++){
        free(graph[i]);
    }
    free(graph);
    free(adj);
    return 0;
}
