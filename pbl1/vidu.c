#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>

// make color
#define BLACK   "\x1B[30m"
#define RED     "\x1B[31m"
#define GREEN   "\x1B[32m"
#define YELLOW  "\x1B[33m"
#define BLUE    "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN    "\x1B[36m"
#define WHITE   "\x1B[37m"
#define RESET   "\x1B[0m"
#define BOLD    "\x1B[1m"
//mau nen
#define BG_BLACK   "\x1B[40m"
#define BG_RED     "\x1B[41m"
#define BG_GREEN   "\x1B[42m"
#define BG_YELLOW  "\x1B[43m"
#define BG_BLUE    "\x1B[44m"
#define BG_MAGENTA "\x1B[45m"
#define BG_CYAN    "\x1B[46m"
#define BG_WHITE   "\x1B[47m"
#define BG_WHILE_B "\x1B[107m"
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

int convertMatrixToList(int **graph, Edge *adj, int v){
    int count = 0;
    for(int i=1; i<=v; i++){
        for(int j=1; j<=v; j++){
            if(graph[i][j] != 0){
                addEdge(adj, i, j, graph[i][j]);
                count++;
            }
        }
    }
    return count;
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
void dijkstra(int v, Edge *adj, int begin, int end, int *path, int *npath, int edgecount) {
    int *L = (int*)malloc((v+1)*sizeof(int));
    int *P = (int*)malloc((v+1)*sizeof(int));
    int *visited = (int*)malloc((v+1)*sizeof(int));

    if(!L || !P || !visited){
        printf(RED "Loi cap phat bo nho!\n" RESET);
        exit(1);
    }

    for (int i = 1; i <= v; i++){
        L[i] = INT_MAX; P[i] = 0; visited[i] = 0;
    }
    L[begin] = 0;

    minHeap* MH = createMinHeap(edgecount);
    add(MH, begin, 0);


    FILE *fout = fopen("outp.txt", "w");
    // in dong dau tien cua bang
    for(int i = 1; i <= v; i++){
        fprintf(fout,"(%3d )\t\t\t", i);
    }
    fprintf(fout,"\n");
    for(int i = 1; i <= v; i++){
        fprintf(fout,"________________");
    }    
    fprintf(fout,"\n");

    //vong lap chinh
    while (MH->size > 0) {
        minHeapNode minNode = poll(MH);
        int u = minNode.vertex;
        int distance = minNode.distance;
        if(L[u] < distance) continue; 

        //In bang 
        for(int i = 1; i <= v; i++){
            if(visited[i]){
                fprintf(fout,"(   --   )\t\t");
                continue;
            }
            if(L[i] == INT_MAX) fprintf(fout,"(INF,%3d )\t\t", P[i]);
            else fprintf(fout,"(%3d,%3d )\t\t", L[i], P[i]);
        }
        fprintf(fout,"\n"); 
        visited[u] = 1; 

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
    fprintf(fout,"\nTong trong so cua duong di ngan nhat tu (%d) den (%d) la: %d\n", begin, end, L[end]);
    fprintf(fout,"Duong di:\n");
    printf(BOLD "\nTong trong so cua duong di ngan nhat tu (%d) den (%d) la: " YELLOW "%d\n" RESET, begin, end, L[end]);
    printf(BOLD "Duong di:\n" RESET);

    int p = end;
    path[(*npath)++] = p; 
    while(P[p] != 0){
        path[(*npath)++] = P[p];
        p = P[p];
    }

    for(int i = (*npath) - 1; i > 0; i--){
        fprintf(fout,"(%d) -> ",path[i]);
        printf("(" BOLD YELLOW "%d" RESET ") -> ",path[i]);
    }
    fprintf(fout,"(%d)\n",path[0]);
    printf("(" BOLD YELLOW "%d" RESET ")\n",path[0]);

    fclose(fout);
    printf("Xuat thanh cong ra file outp.txt\n");

    free(L); free(P); free(visited);
    free(MH->node);
    free(MH);
}

//tao file ve do thi
void xuatGraphviz(Edge *adj, int v, int *path, int npath) {
    FILE* f = fopen("graph.dot", "w");
    if (!f) {
        printf("Loi mo file!\n");
        return;
    }

    fprintf(f, "digraph G {\n");
   // fprintf(f, "  layout=sfdp;\n");   // Dùng sfdp để vẽ đồ thị tốt hơn với đồ thị lớn
    fprintf(f, "  overlap=scale;\n"); // Tránh chồng lấn, tự động co giãn
    fprintf(f, "  sep=\"+1\";\n");     // Tăng khoảng cách giữa các nhóm đỉnh
    fprintf(f, "  nodesep=1.2;\n");   // Khoảng cách giữa các đỉnh (mặc định là 0.25)
    fprintf(f, "  ranksep=1.5;\n");   // Khoảng cách giữa các tầng
    fprintf(f, "  splines=true;\n");  // Vẽ cạnh mượt hơn, tránh bị gấp khúc
    fprintf(f, "  node [shape=circle, style=filled, fillcolor=lightblue, fontcolor=black, fontsize=10, width=0.8, height=0.8];\n");
    fprintf(f, "  edge [color=blue, penwidth=2, fontcolor=red, fontsize=13];\n");

    //tu them to mau cho cac dinh, canh
    fprintf(f, "  %d [fillcolor=cyan,style=filled,color=red, penwidth=5];\n", path[npath-1]);
    fprintf(f, "  %d [fillcolor=cyan,style=filled,color=red, penwidth=5];\n", path[0]);
    for (int i = 1; i <= v; i++) {
        if(i==path[0] || i==path[npath-1]) continue;
        int checknode = 0;
        for (int k = 0; k < npath; k++) {
            if (path[k] == i) {
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
        Edge temp = adj[i];
        while(temp != NULL) {
            int dinh = temp->v;
            int w = temp->w;
            //kiem tra xem canh nay co thuoc duong di ngan nhat khong
            int check = 0;
            for(int k = npath-1; k > 0; k--){
                if((path[k] == i && path[k-1] == dinh)){
                    check = 1; break;
                }
            }
            if(check)
                fprintf(f, "  %d -> %d [label=\"%d\", color=orange, penwidth = 5];\n", i, dinh, w);
            else
                fprintf(f, "  %d -> %d [label=\"%d\", color=black];\n", i, dinh, w);
            temp = temp->next;
        }
    }

    fprintf(f, "}\n");

    fclose(f);
    printf("Xuat thanh cong ra file graph.dot!\nfdp -Tpng graph.dot -o graph.png\n");
} 

void printBanner() {
    system("clear || cls");
    printf(BOLD BLUE "\n");
    printf("\t\t\t  ____  ____   _      \n");
    printf("\t\t\t |  _ \\| __ ) | |     \n");
    printf("\t\t\t | |_) |  _ \\ | |     \n");
    printf("\t\t\t |  __/| |_) || |___  \n");
    printf("\t\t\t |_|   |____/ |_____| \n");
    printf(RESET);
    printf(BOLD YELLOW "           PBL1 - DIJKSTRA'S ALGORITHM VISUALIZER\n\n" RESET);
}


int main() {
    printBanner();
    int v , begin , end;
    printf(BOLD WHITE BG_BLUE " MENU " RESET "\n");
    printf(CYAN "1. Chon do thi co san\n" RESET);
    printf(CYAN "2. Nhap do thi moi\n" RESET);
    printf("Lua chon cua ban: ");
    int x;
    scanf("%d",&x);
    switch(x){
        case 1:{
            FILE *fg;
            printf(BOLD CYAN "Chon do thi:\n" RESET);
            printf(CYAN "Do thi 1 " RED "(15 canh)\n" RESET);
            printf(CYAN "Do thi 2 " RED "(8 canh)\n" RESET);
            printf(CYAN "Do thi 3 " RED "(20 canh)\n" RESET);
            printf(CYAN "Do thi 4 " RED "(100 canh)\n" RESET);
            printf("Lua chon cua ban: ");
            int z; scanf("%d", &z);
            switch(z){
                case 1:
                fg = fopen("dothi1.txt", "r");
                break;
                case 2:
                fg = fopen("dothi2.txt", "r");
                break;
                case 3:
                fg = fopen("dothi3.txt", "r");
                break;
                case 4:
                fg = fopen("dothi4.txt", "r");
                break;
                default:
                printf("khong ton tai do thi nay!!!\n");
                return 1;
            }
            
            fscanf(fg,"%d",&v);
            int *path;
            int npath = 0;
            path = (int*)malloc((v+1)*sizeof(int));
            if(!path){
                printf("Loi cap phat bo nho!\n");
                return 1;
            }

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
                fscanf(fg,"%d", &graph[i][j]);

            }
            fclose(fg);

            printf("Nhap dinh bat dau va dinh ket thuc (trong khoang " YELLOW "1" RESET "->" YELLOW "%d" RESET "): ",v);
            scanf("%d%d", &begin, &end);
            if (begin < 1 || begin > v || end < 1 || end > v) {
                printf(RED "Dinh bat dau hoac ket thuc khong hop le!\n" RESET);
                return 1;
            }

            Edge *adj = (struct edge**)malloc((v+1)*sizeof(struct edge*));
            if(!adj){
                printf("Loi cap phat bo nho!\n");
                return 1;
            }
            for(int i=0; i<=v; i++){
                adj[i] = NULL;
            }

            int edgecount = convertMatrixToList(graph, adj, v);
            dijkstra(v, adj, begin, end, path, &npath, edgecount);
            xuatGraphviz(adj, v, path, npath);

            //giai phong bo nho cap phat dong
            for(int i = 0; i <= v; i++){
                free(graph[i]);
            }
            free(graph);
            for(int i=1; i<= v; i++){
                Edge temp = adj[i];
                while (temp) {
                    Edge next = temp->next;
                    free(temp);
                    temp = next;
                }
            }
            free(adj);
            free(path);
            break;
        }
        default: {
            printf("nhap so dinh cua do thi: "); scanf("%d",&v);
            int *path;
            int npath = 0;
            path = (int*)malloc((v+1)*sizeof(int));
            if(!path){
                printf("Loi cap phat bo nho!\n");
                return 1;
            }

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

            //nhap ma tran trong so
            printf("nhap ma tran trong so: \n");
            for (int i = 1; i <= v; i++){
                for (int j = 1; j <= v; j++)
                scanf("%d", &graph[i][j]);

            }
            printf("Nhap dinh bat dau va dinh ket thuc (trong khoang " YELLOW "1" RESET "->" YELLOW "%d" RESET "): ",v);
            scanf("%d%d", &begin, &end);
            if (begin < 1 || begin > v || end < 1 || end > v) {
                printf(RED "Dinh bat dau hoac ket thuc khong hop le!\n" RESET);
                return 1;
            }

            Edge *adj = (struct edge**)malloc((v+1)*sizeof(struct edge*));
            if(!adj){
                printf("Loi cap phat bo nho!\n");
                return 1;
            }
            for(int i=0; i<=v; i++){
                adj[i] = NULL;
            }

            int edgecount = convertMatrixToList(graph, adj, v);
            dijkstra(v, adj, begin, end, path, &npath, edgecount);
            xuatGraphviz(adj, v, path, npath);

            //giai phong bo nho cap phat dong
            for(int i = 0; i <= v; i++){
                free(graph[i]);
            }
            free(graph);
            for(int i=1; i<= v; i++){
                Edge temp = adj[i];
                while (temp) {
                    Edge next = temp->next;
                    free(temp);
                    temp = next;
                }
            }
            free(adj);
            free(path);
            break;
        }
    }
    return 0;
}
