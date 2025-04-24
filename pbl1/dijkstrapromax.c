#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <sys/stat.h>

// *********************** CÁC ĐỊNH NGHĨA MÀU VÀ KIỂU DỮ LIỆU ***********************
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
#define DIM     "\x1B[2m"
#define ITALIC  "\x1B[3m"
#define UNDERLINE "\x1B[4m"
#define BLINK   "\x1B[5m"
#define REVERSE "\x1B[7m"
#define HIDDEN  "\x1B[8m"

// Màu nền
#define BG_BLACK   "\x1B[40m"
#define BG_RED     "\x1B[41m"
#define BG_GREEN   "\x1B[42m"
#define BG_YELLOW  "\x1B[43m"
#define BG_BLUE    "\x1B[44m"
#define BG_MAGENTA "\x1B[45m"
#define BG_CYAN    "\x1B[46m"
#define BG_WHITE   "\x1B[47m"

// Cấu trúc cho cạnh đồ thị
typedef struct edge {
    int v, w;
    struct edge* next;
} *Edge;

// Cấu trúc cho đỉnh đồ thị
typedef struct vertex {
    int x, y;  // Tọa độ để vẽ đồ thị
    char name[20]; // Tên đỉnh (có thể là chữ)
} Vertex;

// Cấu trúc cho đồ thị
typedef struct graph {
    int V;          // Số đỉnh
    int E;          // Số cạnh
    Edge *adj;      // Danh sách kề
    Vertex *vertices; // Thông tin các đỉnh
} Graph;

// Cấu trúc cho node min heap
typedef struct minHeapNode {
    int vertex;
    int distance;
} minHeapNode;

// Cấu trúc cho min heap
typedef struct minHeap {
    minHeapNode* node;
    int size;
    int capacity;
} minHeap;

// *********************** CÁC HÀM TIỆN ÍCH ***********************
// Tạo thư mục nếu chưa tồn tại
void createDirIfNotExists(const char *path) {
    struct stat st = {0};
    if (stat(path, &st) == -1) {
        mkdir(path, 0700);
    }
}

// Xóa màn hình console
void clearScreen() {
    system("clear || cls");
}

// Hiệu ứng loading
void loadingAnimation(int seconds) {
    printf(BOLD BLUE "\nLoading");
    for(int i = 0; i < seconds; i++) {
        printf(".");
        fflush(stdout);
        sleep(1);
    }
    printf(RESET "\n");
}

// *********************** CÁC HÀM XỬ LÝ ĐỒ THỊ ***********************
// Thêm cạnh vào đồ thị
void addEdge(Graph *g, int u, int v, int w) {
    Edge e = (Edge)malloc(sizeof(struct edge));
    e->v = v; e->w = w;
    e->next = g->adj[u];
    g->adj[u] = e;
    g->E++;
}

// Khởi tạo đồ thị
Graph* createGraph(int V) {
    Graph *g = (Graph*)malloc(sizeof(Graph));
    g->V = V;
    g->E = 0;
    g->adj = (Edge*)malloc((V+1)*sizeof(Edge));
    g->vertices = (Vertex*)malloc((V+1)*sizeof(Vertex));
    
    for(int i = 0; i <= V; i++) {
        g->adj[i] = NULL;
        g->vertices[i].x = rand() % 100;
        g->vertices[i].y = rand() % 100;
        sprintf(g->vertices[i].name, "%d", i);
    }
    
    return g;
}

// Đọc đồ thị từ file
Graph* readGraphFromFile(const char *filename) {
    FILE *fg = fopen(filename, "r");
    if(!fg) {
        printf(RED "Không thể mở file %s!\n" RESET, filename);
        return NULL;
    }
    
    int V;
    fscanf(fg, "%d", &V);
    Graph *g = createGraph(V);
    
    for(int i = 1; i <= V; i++) {
        for(int j = 1; j <= V; j++) {
            int weight;
            fscanf(fg, "%d", &weight);
            if(weight != 0) {
                addEdge(g, i, j, weight);
            }
        }
    }
    
    fclose(fg);
    return g;
}

// Giải phóng bộ nhớ đồ thị
void freeGraph(Graph *g) {
    if(!g) return;
    
    for(int i = 1; i <= g->V; i++) {
        Edge temp = g->adj[i];
        while(temp) {
            Edge next = temp->next;
            free(temp);
            temp = next;
        }
    }
    
    free(g->adj);
    free(g->vertices);
    free(g);
}

// *********************** CÁC HÀM XỬ LÝ MIN HEAP ***********************
// Tạo min heap
minHeap* createMinHeap(int capacity) {
    minHeap* m = (minHeap*)malloc(sizeof(minHeap));
    m->node = (minHeapNode*)malloc((capacity + 1) * sizeof(minHeapNode));
    m->size = 0;
    m->capacity = capacity;
    return m;
}

// Hoán đổi 2 node trong heap
void swap(minHeap* m, int i, int j) {
    minHeapNode temp = m->node[i];
    m->node[i] = m->node[j];
    m->node[j] = temp;
}

// Điều chỉnh heap từ dưới lên
void heapifyUp(minHeap* m, int i) {
    while(i > 1 && m->node[i/2].distance > m->node[i].distance) {
        swap(m, i, i/2);
        i /= 2;
    }
}

// Điều chỉnh heap từ trên xuống
void heapifyDown(minHeap* m, int i) {
    while(2*i <= m->size) {
        int leftChild = 2*i;
        int rightChild = leftChild + 1;
        int smallest = leftChild;
        
        if(rightChild <= m->size && m->node[rightChild].distance < m->node[leftChild].distance) {
            smallest = rightChild;
        }

        if(m->node[i].distance <= m->node[smallest].distance) break;

        swap(m, i, smallest);
        i = smallest;
    }
}

// Thêm node vào heap
void add(minHeap* m, int vertex, int distance) {
    if(m->size >= m->capacity) {
        printf(RED "Heap đã đầy!\n" RESET);
        return;
    }
    
    m->size++;
    m->node[m->size].vertex = vertex;
    m->node[m->size].distance = distance;
    heapifyUp(m, m->size);
}

// Lấy node có khoảng cách nhỏ nhất
minHeapNode poll(minHeap* m) {
    if(m->size == 0) {
        printf(RED "Heap rỗng!\n" RESET);
        minHeapNode empty = {-1, -1};
        return empty;
    }
    
    minHeapNode root = m->node[1];
    m->node[1] = m->node[m->size];
    m->size--;
    heapifyDown(m, 1);
    return root;
}

// Giải phóng bộ nhớ heap
void freeMinHeap(minHeap* m) {
    if(!m) return;
    free(m->node);
    free(m);
}

// *********************** THUẬT TOÁN DIJKSTRA ***********************
// Thuật toán Dijkstra
void dijkstra(Graph *g, int begin, int end, int *path, int *npath) {
    int V = g->V;
    int *L = (int*)malloc((V+1)*sizeof(int));
    int *P = (int*)malloc((V+1)*sizeof(int));
    int *visited = (int*)malloc((V+1)*sizeof(int));

    if(!L || !P || !visited) {
        printf(RED "Lỗi cấp phát bộ nhớ!\n" RESET);
        exit(1);
    }

    // Khởi tạo các giá trị ban đầu
    for(int i = 1; i <= V; i++) {
        L[i] = INT_MAX;
        P[i] = 0;
        visited[i] = 0;
    }
    L[begin] = 0;

    minHeap* MH = createMinHeap(g->E);
    add(MH, begin, 0);

    // Tạo thư mục output nếu chưa tồn tại
    createDirIfNotExists("output");
    
    // Mở file để ghi quá trình thực hiện thuật toán
    FILE *fout = fopen("output/dijkstra_process.txt", "w");
    if(!fout) {
        printf(RED "Không thể tạo file output!\n" RESET);
        return;
    }

    // In tiêu đề bảng
    fprintf(fout, "BẢNG QUÁ TRÌNH THỰC HIỆN THUẬT TOÁN DIJKSTRA\n");
    fprintf(fout, "Đỉnh xuất phát: %d, Đỉnh đích: %d\n\n", begin, end);
    
    for(int i = 1; i <= V; i++) {
        fprintf(fout, "(%3s )\t\t", g->vertices[i].name);
    }
    fprintf(fout, "\n");
    for(int i = 1; i <= V; i++) {
        fprintf(fout, "----------------");
    }    
    fprintf(fout, "\n");

    // Vòng lặp chính của thuật toán
    while(MH->size > 0) {
        minHeapNode minNode = poll(MH);
        int u = minNode.vertex;
        int distance = minNode.distance;
        
        if(L[u] < distance) continue;

        // In trạng thái hiện tại của các đỉnh
        for(int i = 1; i <= V; i++) {
            if(visited[i]) {
                fprintf(fout, "(   --   )\t");
                continue;
            }
            if(L[i] == INT_MAX) {
                fprintf(fout, "(INF,%3d )\t", P[i]);
            } else {
                fprintf(fout, "(%3d,%3d )\t", L[i], P[i]);
            }
        }
        fprintf(fout, "\n"); 
        visited[u] = 1;

        // Dừng nếu đã xét đến đỉnh đích
        if(u == end) break;

        // Cập nhật khoảng cách đến các đỉnh kề
        Edge temp = g->adj[u];
        while(temp != NULL) {
            int v = temp->v;
            int w = temp->w;

            if(!visited[v] && L[u] + w < L[v]) {
                L[v] = L[u] + w;
                add(MH, v, L[v]);
                P[v] = u;
            }
            temp = temp->next;
        }
    }

    // Ghi kết quả vào file
    fprintf(fout, "\nKẾT QUẢ:\n");
    fprintf(fout, "Tổng trọng số đường đi ngắn nhất từ (%d) đến (%d): %d\n", begin, end, L[end]);
    fprintf(fout, "Đường đi:\n");

    // Tìm đường đi ngắn nhất
    *npath = 0;
    int p = end;
    path[(*npath)++] = p; 
    while(P[p] != 0) {
        path[(*npath)++] = P[p];
        p = P[p];
    }

    // In đường đi ngược từ đích về nguồn
    for(int i = (*npath)-1; i > 0; i--) {
        fprintf(fout, "(%s) -> ", g->vertices[path[i]].name);
    }
    fprintf(fout, "(%s)\n", g->vertices[path[0]].name);

    fclose(fout);
    freeMinHeap(MH);
    free(L); free(P); free(visited);
}

// *********************** CÁC HÀM XUẤT ĐỒ THỊ ***********************
// Xuất đồ thị sang định dạng DOT để vẽ bằng Graphviz
void exportGraphToDot(Graph *g, int *path, int npath, const char *filename) {
    FILE* f = fopen(filename, "w");
    if(!f) {
        printf(RED "Không thể tạo file DOT!\n" RESET);
        return;
    }

    fprintf(f, "digraph G {\n");
    fprintf(f, "  layout=neato;\n");
    fprintf(f, "  overlap=scale;\n");
    fprintf(f, "  sep=\"+1\";\n");
    fprintf(f, "  nodesep=1.2;\n");
    fprintf(f, "  ranksep=1.5;\n");
    fprintf(f, "  splines=true;\n");
    fprintf(f, "  node [shape=circle, style=filled, fillcolor=lightblue, fontcolor=black, fontsize=10, width=0.8, height=0.8];\n");
    fprintf(f, "  edge [color=blue, penwidth=2, fontcolor=red, fontsize=13];\n");

    // Đặt vị trí các đỉnh
    for(int i = 1; i <= g->V; i++) {
        fprintf(f, "  %d [pos=\"%d,%d!\", label=\"%s\"];\n", i, g->vertices[i].x, g->vertices[i].y, g->vertices[i].name);
    }

    // Tô màu các đỉnh trên đường đi ngắn nhất
    fprintf(f, "  %d [fillcolor=green, style=filled, color=red, penwidth=3];\n", path[npath-1]); // Đỉnh bắt đầu
    fprintf(f, "  %d [fillcolor=red, style=filled, color=red, penwidth=3];\n", path[0]); // Đỉnh kết thúc
    
    for(int i = 1; i < npath-1; i++) {
        fprintf(f, "  %d [fillcolor=yellow, style=filled, penwidth=3];\n", path[i]);
    }

    // Thêm các cạnh vào đồ thị
    for(int i = 1; i <= g->V; i++) {
        Edge temp = g->adj[i];
        while(temp != NULL) {
            int v = temp->v;
            int w = temp->w;
            
            // Kiểm tra xem cạnh này có thuộc đường đi ngắn nhất không
            int isPathEdge = 0;
            for(int k = npath-1; k > 0; k--) {
                if(path[k] == i && path[k-1] == v) {
                    isPathEdge = 1;
                    break;
                }
            }
            
            if(isPathEdge) {
                fprintf(f, "  %d -> %d [label=\"%d\", color=orange, penwidth=5];\n", i, v, w);
            } else {
                fprintf(f, "  %d -> %d [label=\"%d\"];\n", i, v, w);
            }
            temp = temp->next;
        }
    }

    fprintf(f, "}\n");
    fclose(f);
}

// Tạo file ảnh từ file DOT sử dụng Graphviz
void generateGraphImage(const char *dotFile, const char *outputFile) {
    char command[256];
    sprintf(command, "dot -Tpng %s -o %s", dotFile, outputFile);
    system(command);
}

// *********************** CÁC HÀM GIAO DIỆN NGƯỜI DÙNG ***********************
// Hiển thị banner chương trình
void printBanner() {
    clearScreen();
    printf(BOLD BLUE "\n");
    printf("\t\t\t  ____  ____   _      \n");
    printf("\t\t\t |  _ \\| __ ) | |     \n");
    printf("\t\t\t | |_) |  _ \\ | |     \n");
    printf("\t\t\t |  __/| |_) || |___  \n");
    printf("\t\t\t |_|   |____/ |_____| \n");
    printf(RESET);
    printf(BOLD YELLOW "           PBL1 - DIJKSTRA'S ALGORITHM VISUALIZER\n\n" RESET);
    printf(BOLD MAGENTA "           PHIÊN BẢN NÂNG CẤP - ĐỒ HỌA & TÍNH NĂNG MỞ RỘNG\n\n" RESET);
}

// Hiển thị menu chính
int showMainMenu() {
    printf(BOLD WHITE BG_BLUE " MENU CHÍNH " RESET "\n");
    printf(CYAN "1. Chọn đồ thị có sẵn\n" RESET);
    printf(CYAN "2. Nhập đồ thị mới\n" RESET);
    printf(CYAN "3. Thoát chương trình\n" RESET);
    printf("Lựa chọn của bạn: ");
    
    int choice;
    scanf("%d", &choice);
    return choice;
}

// Hiển thị menu chọn đồ thị
int showGraphMenu() {
    printf(BOLD CYAN "\nChọn đồ thị:\n" RESET);
    printf(CYAN "1. Đồ thị 1 " RED "(15 cạnh)\n" RESET);
    printf(CYAN "2. Đồ thị 2 " RED "(8 cạnh)\n" RESET);
    printf(CYAN "3. Đồ thị 3 " RED "(20 cạnh)\n" RESET);
    printf(CYAN "4. Đồ thị 4 " RED "(100 cạnh)\n" RESET);
    printf(CYAN "5. Quay lại menu chính\n" RESET);
    printf("Lựa chọn của bạn: ");
    
    int choice;
    scanf("%d", &choice);
    return choice;
}

// Nhập đồ thị từ người dùng
Graph* inputGraphFromUser() {
    int V;
    printf("Nhập số đỉnh của đồ thị: ");
    scanf("%d", &V);
    
    Graph *g = createGraph(V);
    
    printf("Nhập ma trận trọng số (%dx%d):\n", V, V);
    for(int i = 1; i <= V; i++) {
        for(int j = 1; j <= V; j++) {
            int weight;
            scanf("%d", &weight);
            if(weight != 0) {
                addEdge(g, i, j, weight);
            }
        }
    }
    
    return g;
}

// Hiển thị kết quả đường đi ngắn nhất
void displayShortestPath(Graph *g, int *path, int npath, int begin, int end, int distance) {
    printf(BOLD "\nTổng trọng số của đường đi ngắn nhất từ (%s) đến (%s) là: " YELLOW "%d\n" RESET, 
           g->vertices[begin].name, g->vertices[end].name, distance);
    printf(BOLD "Đường đi:\n" RESET);

    for(int i = npath-1; i > 0; i--) {
        printf("(" BOLD YELLOW "%s" RESET ") -> ", g->vertices[path[i]].name);
    }
    printf("(" BOLD YELLOW "%s" RESET ")\n", g->vertices[path[0]].name);
}

// *********************** HÀM MAIN ***********************
int main() {
    srand(time(NULL)); // Khởi tạo seed cho random
    
    while(1) {
        printBanner();
        int mainChoice = showMainMenu();
        
        if(mainChoice == 3) {
            printf(BOLD GREEN "\nCảm ơn đã sử dụng chương trình!\n" RESET);
            break;
        }
        
        Graph *g = NULL;
        int begin, end;
        
        if(mainChoice == 1) {
            while(1) {
                int graphChoice = showGraphMenu();
                
                if(graphChoice == 5) break;
                
                char *filename;
                switch(graphChoice) {
                    case 1: filename = "dothi1.txt"; break;
                    case 2: filename = "dothi2.txt"; break;
                    case 3: filename = "dothi3.txt"; break;
                    case 4: filename = "dothi4.txt"; break;
                    default: 
                        printf(RED "Lựa chọn không hợp lệ!\n" RESET);
                        continue;
                }
                
                loadingAnimation(2);
                g = readGraphFromFile(filename);
                if(!g) continue;
                
                printf(BOLD GREEN "\nĐã tải đồ thị thành công từ file %s!\n" RESET, filename);
                printf("Số đỉnh: %d, Số cạnh: %d\n", g->V, g->E);
                
                printf("\nNhập đỉnh bắt đầu và đỉnh kết thúc (1-%d): ", g->V);
                scanf("%d%d", &begin, &end);
                
                if(begin < 1 || begin > g->V || end < 1 || end > g->V) {
                    printf(RED "Đỉnh bắt đầu hoặc kết thúc không hợp lệ!\n" RESET);
                    freeGraph(g);
                    g = NULL;
                    continue;
                }
                
                break;
            }
        } 
        else if(mainChoice == 2) {
            g = inputGraphFromUser();
            if(!g) continue;
            
            printf(BOLD GREEN "\nĐã nhập đồ thị thành công!\n" RESET);
            printf("Số đỉnh: %d, Số cạnh: %d\n", g->V, g->E);
            
            printf("\nNhập đỉnh bắt đầu và đỉnh kết thúc (1-%d): ", g->V);
            scanf("%d%d", &begin, &end);
            
            if(begin < 1 || begin > g->V || end < 1 || end > g->V) {
                printf(RED "Đỉnh bắt đầu hoặc kết thúc không hợp lệ!\n" RESET);
                freeGraph(g);
                g = NULL;
                continue;
            }
        } 
        else {
            printf(RED "Lựa chọn không hợp lệ!\n" RESET);
            continue;
        }
        
        if(!g) continue;
        
        // Cấp phát bộ nhớ cho đường đi
        int *path = (int*)malloc((g->V+1)*sizeof(int));
        int npath = 0;
        
        if(!path) {
            printf(RED "Lỗi cấp phát bộ nhớ!\n" RESET);
            freeGraph(g);
            continue;
        }
        
        // Thực hiện thuật toán Dijkstra
        loadingAnimation(3);
        dijkstra(g, begin, end, path, &npath);
        
        // Hiển thị kết quả
        int distance = 0;
        for(int i = npath-1; i > 0; i--) {
            Edge temp = g->adj[path[i]];
            while(temp && temp->v != path[i-1]) temp = temp->next;
            if(temp) distance += temp->w;
        }
        
        displayShortestPath(g, path, npath, begin, end, distance);
        
        // Xuất đồ thị sang định dạng DOT và tạo ảnh
        printf("\nĐang tạo hình ảnh đồ thị...\n");
        createDirIfNotExists("output");
        exportGraphToDot(g, path, npath, "output/graph.dot");
        generateGraphImage("output/graph.dot", "output/graph.png");
        
        printf(GREEN "\nKết quả đã được lưu vào thư mục output:\n");
        printf("- Quá trình thực hiện thuật toán: dijkstra_process.txt\n");
        printf("- Đồ thị dạng DOT: graph.dot\n");
        printf("- Hình ảnh đồ thị: graph.png\n" RESET);
        
        // Giải phóng bộ nhớ
        free(path);
        freeGraph(g);
        
        printf("\nNhấn Enter để tiếp tục...");
        getchar(); getchar();
    }
    
    return 0;
}