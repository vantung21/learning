#include<stdio.h>
#include<limits.h>
#include<stdlib.h>

int a[1000001], s=0;

typedef struct minHeapNode{
    int vertex;
    int distance;
}minHeapNode;

typedef struct minHeap{
    minHeapNode* node;
    int size;
}minHeap;

// void swap(minHeap* m, int i, int j){
//     int t = m->node[i].distance;
//     m->node[i].distance = m->node[j].distance;
//     m->node[j].distance = t;
// }
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
    int curIndex = i;
    int parentIndex = i/2;
    while(parentIndex !=0 && m->node[parentIndex].distance > m->node[curIndex].distance){
        swap(m, parentIndex, curIndex);
        curIndex = parentIndex;
        parentIndex = curIndex/2;
    }
}

void heapifyDown(minHeap* m, int i){
    int curIndex = i;
    while(curIndex*2 <= m->size){
        int leftChildIndex = curIndex*2;
        int rightChildIndex = leftChildIndex + 1;
        int smallerChildIndex = leftChildIndex;
        if(rightChildIndex <= m->size && m->node[rightChildIndex].distance < m->node[smallerChildIndex].distance){
            smallerChildIndex = rightChildIndex;
        }
        if(m->node[curIndex].distance > m->node[smallerChildIndex].distance){
            swap(m, curIndex, smallerChildIndex);
            curIndex = smallerChildIndex;
        }
        else{
            break;
        }
    }
}

void add(minHeap* m, int vertex, int distance){
    int i =++m->size;
    m->node[i].distance = distance;
    m->node[i].vertex = vertex;

    //heapify_up
    heapifyUp(m, i);

}
minHeapNode poll(minHeap* m){
    minHeapNode root = m->node[1];
    m->node[1] = m->node[m->size];
    m->size--;

    //heapify_down
    heapifyDown(m, 1);
    
    return root;
}

int isEmpty(minHeap m){
    return m.size <= 0;
}

//xoa phan tu trong minHeap
void Remove(minHeap* m, int vertex){
    int curIndex = -1;
    for(int i=1; i<=m->size; i++){
        if(m->node[i].vertex == vertex){
           curIndex = i; break; 
        }
    }
    if(curIndex == -1){
        //printf("error: Element is not exist!!\n");
        return;
    }

    m->node[curIndex] = m->node[m->size];
    m->size--;
    
    if(curIndex/2 > 0 && m->node[curIndex].distance<m->node[curIndex/2].distance){
        //heapify_up
        heapifyUp(m, curIndex);
    }
    else {
        //hepify_down
        heapifyDown(m, curIndex);
    }
}

// dijkstra
void dijkstra(int v,int** graph, int source, int sink){
    int L[v+1], P[v+1];
    for(int i=1; i<=v; i++){
        P[i] = 0;
    }
    for(int i=1; i<=v; i++){
        L[i] = INT_MAX;
    }
    L[source] = 0;
    
    minHeap* MH = createMinHeap(v+1);
    add(MH, source, 0);

    while(!isEmpty(*MH)){
        minHeapNode minNode = poll(MH);
        int u = minNode.vertex;

        //cap nhap khoang cach cho cac dinh ke
        for(int i=1; i<=v; i++){
            if(graph[u][i] != 0 && L[u] != INT_MAX && L[u]+graph[u][i] < L[i]){
                L[i] = L[u]+graph[u][i];
                Remove(MH, i);
                add(MH, i, L[i]);
                P[i]=u;
            }
        }
    }
    printf("duong di ngan nhat tu (%d) den (%d) la: %d\n",source, sink, L[sink]);
    printf("duong di:\n");
    //int a[v+1], s=0;
    int p =sink;
    a[s++] = p; 
    while(P[p] != 0){
        a[s++] = P[p];
        p = P[p];
    }

    for(int i=s-1; i>0; i--){
        printf("(%d) -> ",a[i]);
    }
    printf("(%d)\n",a[0]);
}

//nhap ma tran trong so
void nhap(int** graph, int v){
    printf("nhap ma tran trong so cua do thi(khong am):\n");
    for(int i=1; i<=v; i++){
        for(int j=1; j<=v; j++){
            scanf("%d",&graph[i][j]);
        }
    }

}

//tao file ve do thi 1
/*void xuatGraphviz(int** graph, int v) {
    FILE* f = fopen("graph.dot", "w");
    if (!f) {
        printf("Lỗi mở file!\n");
        return;
    }
    
    fprintf(f, "graph G {\n");
    for (int i = 1; i <= v; i++) {
        for (int j = i + 1; j <= v; j++) {
            if (graph[i][j] != 0) {
                fprintf(f, "  %d -- %d [label=\"%d\"];\n", i, j, graph[i][j]);
            }
        }
    }
    fprintf(f, "}\n");
    
    fclose(f);
    printf("Xuất thành công ra file graph.dot!\n");
} */


//tao file ve do thi 3
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
    fprintf(f, "  edge [color=blue, penwidth=2, fontcolor=red, fontsize=10];\n");

    // for (int i = 1; i <= v; i++) {
    //     for (int j = i + 1; j <= v; j++) {
    //         if (graph[i][j] != 0) {
    //             fprintf(f, "  %d -- %d [label=\"%d\", color=blue];\n", i, j, graph[i][j]);
    //         }
    //     }
    // }

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
    printf("Xuất thành công ra file graph.dot!\n");
} 




        
int main(){
    // freopen("inp.txt","r", stdin);
    // freopen("outp.txt", "w", stdout);
    int v;
    // nhap so luong dinh
    scanf("%d",&v);

    //tao mang dong 2 chieu
    int** graph = (int**)malloc((v+1)*sizeof(int*));
    for(int i=1; i<=v; i++){
        graph[i] = (int*)malloc((v+1)*sizeof(int));
    }

    nhap(graph,v);
    int source, sink;
    scanf("%d%d",&source,&sink);

    dijkstra(v, graph, source, sink);

    xuatGraphviz(graph, v);

    //giai phong bo nho cap phat dong
    for(int i=1; i<=v; i++){
        free(graph[i]);
    }
    free(graph);

    return 0;
}