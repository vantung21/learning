#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include <unistd.h>

//color
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

// background color
#define BG_BLACK   "\x1B[40m"
#define BG_RED     "\x1B[41m"
#define BG_GREEN   "\x1B[42m"
#define BG_YELLOW  "\x1B[43m"
#define BG_BLUE    "\x1B[44m"
#define BG_MAGENTA "\x1B[45m"
#define BG_CYAN    "\x1B[46m"
#define BG_WHITE   "\x1B[47m"
#define BG_WHITE_B "\x1B[107m"

//cau truc cua danh sach ke
typedef struct edge{
    int v, w; 
    struct edge* next;
} *Edge;

// cau truc minHeap
typedef struct minHeapNode{
    int vertex;          // dinh
    int distance;        // khoang cach ngan nhat tu dinh nguon den dinh nay
} minHeapNode;

typedef struct minHeap{
    minHeapNode* node;    // mang luu cac phan tu trong minHeap
    int size;             // so dinh trong minHeap
} minHeap;

// khai bao ham
int** createGraph(int v); // cap phat bo nho cho ma tran trong so
int** randomGraph(int v); 
int** enterMatrixData(int v, int *check); // ham nhap ma tran trong so tu ban phim

void addEdge(Edge *adj, int u, int v, int w);
int convertMatrixToList(int **graph, Edge **adj, int v); // chuyen ma tran trong so sang danh sach ke

// cac ham thao tac trong min heap
void swap(minHeap* m, int i, int j);
minHeap* createMinHeap(int capacity);
void heapifyUp(minHeap* m, int i);
void heapifyDown(minHeap* m, int i);
void add(minHeap* m, int vertex, int distance);
minHeapNode poll(minHeap* m);

void dijkstra(int v, Edge *adj, int begin, int end, int *path, int *npath, int edgecount);

void Bellman_Ford(int v, Edge *adj, int begin, int end, int *path, int *npath);

void exportGraphviz(Edge *adj, int v, int *path, int npath);

// cac ham in menu
void printBanner();
void printWithDelay(const char *line);
void printMainMenu();
void printMenuCreateGraph();
void printMenuRun();
void printMenuViewResult();

void printAdjacencyMatrix(int** graph, int v);
void printAdjacencyList(Edge* adj, int v);

void freeMemory(int*** graph, Edge** adj, int** path, int *npath, int v);
void loadGraphFromFile(int *v, int ***graph, Edge **adj, int *checkNegativeWeight, int *countedge, int **path, int *npath);
void createNewGraph(int *v, int ***graph, Edge **adj, int *checkNegativeWeight, int *countedge, int **path, int *npath);
void runAlgorithm(int v, int **graph, Edge *adj, int checkNegativeWeight, int countedge, int *begin, int *end, int **path, int *npath);   
void viewResult(int v, Edge *adj, int *path, int npath);


int main(){
    int v , begin , end, countedge, npath = 0, checkNegativeWeight = 0;
    int *path = NULL;
    int** graph = NULL;
    Edge *adj = NULL;
    while(1){
        printBanner();
        printMainMenu();
        int choice;
        int checkChoice = scanf("%d",&choice);
        if(checkChoice == 0){
            while(getchar() != '\n');
            continue;
        } 
        if(choice == 1){
            loadGraphFromFile(&v, &graph, &adj, &checkNegativeWeight, &countedge, &path, &npath);
        }
        else if(choice == 2){
            createNewGraph(&v, &graph, &adj, &checkNegativeWeight, &countedge, &path, &npath);
        }
        else if(choice == 3){
            runAlgorithm(v, graph, adj, checkNegativeWeight, countedge, &begin, &end, &path, &npath);
        }
        else if(choice == 4){
            viewResult(v, adj, path, npath);
        }
        else if(choice == 0){
            freeMemory(&graph, &adj, &path, &npath, v);

            printf(BOLD GREEN "Exiting");
            for(int i = 0; i < 3; i++){
                usleep(300000);
                printf(".");
            }
            printf("\r            \rEXITED.");
            printf("\n" RESET);
            break;
        }
        else continue;
    }
    return 0;
}

//cap phat bo nho cho mang 
int** createGraph(int v){
    int** graph = (int**)malloc((v + 1) * sizeof(int*));
    if(graph == NULL){
        printf(BOLD RED "Memory allocation error!\n" RESET);
        exit(1);
    }
    for(int i = 0; i <= v; i++){
        graph[i] = (int*)calloc((v + 1), sizeof(int));
        if(graph[i] == NULL){
            printf(BOLD RED "Memory allocation error!\n" RESET);
            exit(1);
        }
    }
    return graph;
}

int** randomGraph(int v){
    if(v < 3){
        printf(RED "Error: Number of vertices must be at least 3\n" RESET);
        return NULL;
    }
    int** matrix = createGraph(v);
    // Dat gioi han cho so canh , trong so 
    const int max_Weight = 100;
    const double min_EdgesPerVertex = 1.5, max_EdgePerVertex = 2.5; // Tong so canh tu 1.5 den 2.5 lan so dinh 
    const int max_OutInVertex = 3; // so luong canh vao toi da la 3 va so luong canh ra toi da cung la 3

    // Tao mang dem so dinh vao va ra cua 1 dinh
    int *in_v = (int*)calloc(v + 1, sizeof(int));
    int *out_v = (int*)calloc(v + 1, sizeof(int));
    if(in_v == NULL || out_v == NULL){
        printf(BOLD RED "Memory allocation error!\n" RESET);
        exit(1);
    }

    // Tao cay khung de dam bao tinh lien thong
    for(int j = 2; j <= v; j++){
        int i;
        do{
            i = rand() % j;
        } while(out_v[i] >= max_OutInVertex || i == 0);
        matrix[i][j] = 1 + rand() % max_Weight;
        out_v[i]++; in_v[j]++;
    }

    //Tinh so canh mong muon
    int target_edges = (int)(v * (min_EdgesPerVertex + (rand() / (double)RAND_MAX) * (max_EdgePerVertex - min_EdgesPerVertex)));
    int current_edges = v - 1;    // So canh hien co trong do thi

    // Them canh ngau nhien
    while (current_edges < target_edges) {
        int i = rand() % v + 1;
        int j = rand() % v + 1;

        // kiem tra so canh di ra tu i va so canh di vao j da toi da chua 
        while(out_v[i] >= max_OutInVertex){
            i = rand() % v+1;
        }
        while(in_v[j] >= max_OutInVertex){
            j = rand() % v+1;
        }
        // kiem tra da co canh giua i va j chua
        if(i != j && matrix[i][j] == 0){
            matrix[i][j] = 1 + rand() % max_Weight;
            out_v[i]++; in_v[j]++;
            current_edges++;
        }
    }
    free(in_v);
    free(out_v);
    return matrix;
}

int** enterMatrixData(int v, int *checkNegativeWeight){
    int** graph = createGraph(v);

    for(int i = 1; i <= v; i++){
        for(int j = 1; j <= v; j++){
            scanf("%d", &graph[i][j]);            
            if(graph[i][j] < 0) *checkNegativeWeight = 1;
        }
    }   
    return graph;
}

void addEdge(Edge *adj, int u, int v, int w){
    Edge e = (Edge)malloc(sizeof(struct edge));
    e->v = v; e->w = w;
    e->next = adj[u];
    adj[u] = e;
}

int convertMatrixToList(int **graph, Edge **adj, int v){
    *adj = (struct edge**)malloc((v + 1)*sizeof(struct edge*));
    if((*adj) == NULL){
        printf(RED "Memory allocation error!\n" RESET);
        exit(1);
    }
    for(int i = 0; i <= v; i++){
        (*adj)[i] = NULL;
    }
    int count = 0;
    for(int i = 1; i <= v; i++){
        for(int j = 1; j <= v; j++){
            if(graph[i][j] != 0){
                addEdge(*adj, i, j, graph[i][j]);
                count++;
            }
        }
    }
    return count;
}

void swap(minHeap* m, int i, int j){
    minHeapNode temp = m->node[i];
    m->node[i] = m->node[j];
    m->node[j] = temp;
}

minHeap* createMinHeap(int capacity){
    minHeap* m = (minHeap*)malloc(sizeof(minHeap));
    if(m == NULL){
        printf(RED "Memory allocation error!\n" RESET);
        exit(1);
    }
    m->node = (minHeapNode*)malloc((capacity + 1) * sizeof(minHeapNode));
    if(m->node == NULL){
        printf(RED "Memory allocation error!\n" RESET);
        exit(1);
    }
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

//dijkstra
void dijkstra(int v, Edge *adj, int begin, int end, int *path, int *npath, int edgecount){
    *npath = 0;
    int checkBigGraph = 0;
    if(v > 30) checkBigGraph = 1;
    if(checkBigGraph) 
        printf(BOLD YELLOW 
        "Warning: The graph is too large to display step-by-step execution directly.\n"
        "If you want to view the execution steps, return to the MAIN MENU -> select \"4. View result\" -> then choose \"2. View Dijkstra's algorithm steps\".\n" 
        RESET);
    int *L = (int*)malloc((v + 1)*sizeof(int)); //L la mang luu khoang cach den dinh nguon
    int *P = (int*)calloc((v + 1), sizeof(int)); // P la mang chua dinh truoc dinh do trong duong di
    int *visited = (int*)calloc((v + 1), sizeof(int));

    if(L == NULL || P  == NULL|| visited == NULL){
        printf(RED "Memory allocation error!\n" RESET);
        exit(1);
    }

    for (int i = 1; i <= v; i++){
        L[i] = INT_MAX;
    }
    L[begin] = 0;

    minHeap* MH = createMinHeap(edgecount);
    add(MH, begin, 0);

    if(!checkBigGraph){
        printf(CYAN "\nStarting Dijkstra's algorithm from %d to %d...\n" RESET, begin, end);
        printf("Step-by-step visualization:\n");  usleep(200000);
    }

    int okfile = 1;
    FILE *fout = fopen("outpDijkstra.txt", "w");
    if(fout == NULL){
        printf(RED "Failed to open " YELLOW "outpDijkstra.txt" RED ": cannot write output to file." RESET);
        okfile = 0;
    }
    if(okfile){
        fprintf(fout,"\nStarting Dijkstra's algorithm from %d to %d...\n", begin, end);
        fprintf(fout,"Step-by-step visualization:\n");
    }

    //vong lap chinh
    while (MH->size > 0){
        minHeapNode minNode = poll(MH);
        int u = minNode.vertex;
        int distance = minNode.distance;
        if(visited[u]) continue;
        visited[u] = 1;

        // print step by step
        if(!checkBigGraph){
            printf("\n" BG_BLUE WHITE " Processing vertex %d " RESET "\n", u);
            printf("Current distances:\n");
        }
        if(okfile){
            fprintf(fout, "\n Processing vertex %d \n", u);
            fprintf(fout, "Current distances:\n");
        }
        for(int i = 1; i <= v; i++){
            if(L[i] == INT_MAX){
                if(!checkBigGraph) printf(RED " INF " RESET);
                if(okfile) fprintf(fout, " INF ");
            } else if(i == u){
                if(!checkBigGraph) printf(BOLD BG_GREEN " %3d " RESET, L[i]);
                if(okfile) fprintf(fout, " >%d< ", L[i]);
            } else if(visited[i]){
                if(!checkBigGraph) printf(GREEN " %3d " RESET, L[i]);
                if(okfile) fprintf(fout, " |%d| ", L[i]);
            } else{
                if(!checkBigGraph) printf(" %3d ", L[i]);
                if(okfile) fprintf(fout, " %d ", L[i]);
            }
        }
        if(!checkBigGraph) printf("\n");
        if(okfile) fprintf(fout, "\n");
        if(visited[end]) break;

        Edge temp = adj[u];
        while(temp != NULL){
            int x = temp->v;
            int w = temp->w;

            if(!visited[x] && L[u] + w < L[x]){
                L[x] = L[u] + w;
                add(MH, x, L[x]);
                P[x] = u;
                if(!checkBigGraph) printf("   Relaxing edge %d->%d: new distance = %d\n", u, x, L[x]);
                if(okfile) fprintf(fout, "   Relaxing edge %d->%d: new distance = %d\n", u, x, L[x]);
            }
            temp = temp->next;
        }
        if(!checkBigGraph) usleep(200000);
    }

    printf("\n" BG_YELLOW RED"\n FINAL RESULT " RESET "\n"); usleep(200000);
    if(okfile) fprintf(fout, "\n _FINAL_RESULT_ \n");
    if(L[end] == INT_MAX){
        printf(RED "No path from %d to %d !\n" RESET, begin, end);
        if(okfile) fprintf(fout, "No path from %d to %d !\n", begin, end);
        return;
    }
    //In duong di ngan nhat   
    printf(BOLD "Shortest distance from (%d) to (%d): " YELLOW "%d\n" RESET, begin, end, L[end]); usleep(200000);
    printf(BOLD "Path:\n" RESET);   usleep(200000);
    if(okfile){
        fprintf(fout, "Shortest distance from (%d) to (%d): %d\n", begin, end, L[end]);
        fprintf(fout, "Path:\n");
    }

    int p = end; 
    while(p != 0){
        path[(*npath)++] = p;
        p = P[p];
    }

    for(int i = (*npath) - 1; i > 0; i--){
        if(okfile) fprintf(fout,"(%d) -> ",path[i]);
        printf("(" BOLD YELLOW "%d" RESET ") -> ",path[i]);
        fflush(stdout); usleep(200000);
    }
    if(okfile) fprintf(fout,"(%d)\n",path[0]);
    printf("(" BOLD YELLOW "%d" RESET ")\n",path[0]);

    if(okfile) fclose(fout);

    free(L); free(P); free(visited);
    free(MH->node);
    free(MH);
}

// Bellman_Ford
void Bellman_Ford(int v, Edge *adj, int begin, int end, int *path, int *npath){
    *npath = 0;
    int checkBigGraph = 0;
    if(v > 30) checkBigGraph = 1;
    if(checkBigGraph) 
        printf(BOLD YELLOW 
        "Warning: The graph is too large to display step-by-step execution directly.\n"
        "If you want to view the execution steps, return to the MAIN MENU -> select \"4. View result\" -> then choose \"3. View Bellman-Ford algorithm steps\".\n" 
        RESET);
    int *L = (int*)malloc((v+1)*sizeof(int));
    int *P = (int*)malloc((v+1)*sizeof(int));
    if(L == NULL || P == NULL){
        printf(RED "Memory allocation error!\n" RESET);
        exit(1);
    }
    for(int i = 1; i <= v; i++){
        L[i] = INT_MAX; P[i] = 0; 
    }
    L[begin] = 0;

    int okfile = 1;
    FILE* fout = fopen("outpBellman_Ford.txt","w");
    if(fout == NULL){
        printf(RED "Failed to open " YELLOW "outpBellman_Ford.txt" RED ": cannot write output to file." RESET);
        okfile = 0;
    }
    if(!checkBigGraph){
        printf(CYAN "\nStarting Bellman_Ford's algorithm from %d to %d...\n" RESET, begin, end);
        printf("Step-by-step visualization:\n"); usleep(200000);
    }
    if(okfile){
        fprintf(fout, "\nStarting Bellman_Ford's algorithm from %d to %d...\n", begin, end);
        fprintf(fout,"Step-by-step visualization:\n");
    }

    int changed;
    for(int k = 1; k < v; k++){
        if(!checkBigGraph){
            printf("\n" BG_BLUE WHITE " Iteration %d " RESET "\n",k);
            printf("Current distances:\n");
        }
        if(okfile){
            fprintf(fout, "\n Iteration %d \n",k);
            fprintf(fout, "Current distances:\n");
        }       
        for(int i = 1; i <= v; i++){
            if(L[i] == INT_MAX){
                if(!checkBigGraph) printf(RED " INF " RESET);
                if(okfile) fprintf(fout, " INF ");
            } 
            else{
                if(!checkBigGraph) printf(YELLOW " %3d " RESET, L[i]);
                if(okfile) fprintf(fout, " %3d ", L[i]);
            }
        }
        if(!checkBigGraph) printf("\n");
        if(okfile) fprintf(fout, "\n");

        changed = 0;
        for(int i = 1; i <= v; i++){
            if(L[i] == INT_MAX) continue;
            Edge temp = adj[i];
            while(temp != NULL){
                int x = temp->v;
                int w = temp->w;
                if(L[x] > L[i] + w){
                    L[x] = L[i] + w;
                    P[x] = i;
                    changed = 1;
                    if(!checkBigGraph) printf("   Relaxing edge %d->%d: new distance = %d\n", i, x, L[x]);
                    if(okfile) fprintf(fout, "   Relaxing edge %d->%d: new distance = %d\n", i, x, L[x]);
                }
                temp = temp->next;
            }   
        }
        if(!checkBigGraph) usleep(200000);
        if(changed == 0){
            if(!checkBigGraph) printf(MAGENTA "No changes detected - final distances:\n" RESET);
            if(okfile) fprintf(fout, "No changes detected - final distances:\n");
            if(!checkBigGraph) usleep(200000);
            for(int i = 1; i <= v; i++){
                if(L[i] == INT_MAX){
                    if(!checkBigGraph) printf(RED " INF " RESET);
                    if(okfile) fprintf(fout, " INF ");
                } 
                else{
                    if(!checkBigGraph) printf(GREEN " %3d " RESET, L[i]);
                    if(okfile) fprintf(fout, " %3d ", L[i]);
                }
            }
            if(!checkBigGraph) printf("\n");
            if(okfile) fprintf(fout, "\n");
            break;
        }
    }
    // kiem tra chu trinh am
    if(changed == 1){
        for(int i = 1; i <= v; i++){
            Edge temp = adj[i];
            while(temp != NULL){
                int x = temp->v;
                int w = temp->w;
                if(L[x] > L[i] + w){
                    printf(RED "Graph contains a negative cycle!\n" RESET);
                    if(okfile) fprintf(fout, "Graph contains a negative cycle!\n");
                    free(L); free(P);
                    return;
                }
                temp = temp->next;
            }  
        }
    }
    if(!checkBigGraph) usleep(200000);
    printf("\n" BG_YELLOW RED"\n FINAL RESULT " RESET "\n");    
    if(okfile) fprintf(fout, "\n _FINAL_RESULT_ \n");
    usleep(200000);
    // khong co duong di
    if(L[end] == INT_MAX){
        printf(RED "No path from %d to %d!\n" RESET, begin, end);
        if(okfile) fprintf(fout, "No path from %d to %d!\n", begin, end);
        free(L); free(P);
        return;
    }
    
    //In duong di ngan nhat
    printf(BOLD "Shortest distance from (%d) to (%d): " YELLOW "%d\n" RESET, begin, end, L[end]); usleep(200000);
    printf(BOLD "Path:\n" RESET); usleep(200000);
    if(okfile){
        fprintf(fout, "Shortest distance from (%d) to (%d): %d\n", begin, end, L[end]);
        fprintf(fout, "Path:\n");
    }
    
    int p = end;
    while(p != 0){
        path[(*npath)++] = p;
        p = P[p];
    }
    for(int i = (*npath) - 1; i > 0; i--){
        printf("(" BOLD YELLOW "%d" RESET ") -> ",path[i]);
        if(okfile) fprintf(fout,"(%d) -> ",path[i]);
        fflush(stdout);
        usleep(200000);
    }
    printf("(" BOLD YELLOW "%d" RESET ")\n",path[0]); 
    if(okfile) fprintf(fout,"(%d)\n",path[0]);  
    if(okfile) fclose(fout);
    
    free(L); free(P);
    return;
}

//tao file ve do thi
void exportGraphviz(Edge *adj, int v, int *path, int npath){
    FILE* f = fopen("graph.dot", "w");
    if(f == NULL){
        printf(RED "Error opening file graph.dot!\n" RESET);
        return;
    }

    fprintf(f, "digraph G {\n");
    fprintf(f, "  layout=neato;\n");
    fprintf(f, "  sep=\"+20\"\n"); 
    fprintf(f, "  nodesep=1;\n");  
    fprintf(f, "  overlap=false;\n"); 
    fprintf(f, "  splines=true;\n");  
    fprintf(f, "  node [shape=circle, style=filled, fillcolor=lightblue, fontname=\"Helvetica\"];\n");
    fprintf(f, "  edge [fontname=\"Helvetica\", fontsize=10];\n");

    if(npath == 0){
        if(adj == NULL){
            printf( RED "No graph has been entered!\n" RESET);
            fclose(f);
            return;
        }
        else{
            // ve dinh
            for(int i = 1; i<= v; i++){
                fprintf(f, "  %d [];\n", i);  
            }
            // ve canh
            for(int i = 1; i <= v; i++){
                Edge temp = adj[i];
                while(temp != NULL){
                    int dinh = temp->v;
                    int w = temp->w;
                    fprintf(f, "  %d -> %d [label=\"%d\"];\n", i, dinh, w);
                    temp = temp->next;
                }
            }
        }
    }
    else{
            //to mau cho cac dinh, canh
        for(int i = 1; i<= v; i++){
            fprintf(f, "  %d [];\n", i);  
        }
        for(int i = 0; i < npath; i++){
            fprintf(f, "  %d [fillcolor=gold, style=\"filled,bold\", penwidth=2];\n", path[i]);
        }
        fprintf(f, "  %d [fillcolor=lightgreen, style=\"filled,bold\"];\n", path[0]);
        fprintf(f, "  %d [fillcolor=salmon, style=\"filled,bold\"];\n", path[npath-1]);

        for(int i = 1; i <= v; i++){
            Edge temp = adj[i];
            while(temp != NULL){
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
                    fprintf(f, "  %d -> %d [label=\"%d\", color=red, penwidth=2, fontcolor=red];\n", i, dinh, w);
                else
                    fprintf(f, "  %d -> %d [label=\"%d\"];\n", i, dinh, w);
                temp = temp->next;
            }
        }
    }

    fprintf(f, "}\n");

    fclose(f);

    system("neato -Tpng graph.dot -o graph.png && powershell.exe start graph.png");
} 

void printBanner(){
    system("clear || cls");
    printf("\n\n");
    printf("    " BG_WHITE_B YELLOW "%c", 201);
	for (int i = 1; i < 21; i++){
		printf("%c", 205);
	}
	printf("%c" RESET "    ",187);
    printf(BG_BLUE "      " RESET "%c " BG_BLUE "  " RESET "%c   " BG_BLUE "  " RESET "%c" BG_BLUE "        " RESET"%c              " BG_BLUE "  " RESET"%c" BG_BLUE "        " RESET"%c" BG_BLUE "       " RESET "%c    ", 187, 187, 187, 187, 187, 187, 187);
    printf(BG_WHITE_B BLACK "     @" CYAN "@@@@@@@@@@@@@" BLACK "#    " RESET "\n");
    printf("    " BG_WHITE_B YELLOW "%c" BLUE "   D                " YELLOW "%c" RESET "    ", 186, 186);
    printf( BG_BLUE "  " RESET "%c%c%c" BG_BLUE "  " RESET "%c" BG_BLUE "  " RESET "%c   " BG_BLUE "  " RESET "%c%c%c%c" BG_BLUE "  " RESET "%c%c%c%c              " BG_BLUE "  " RESET "%c%c%c%c" BG_BLUE "  " RESET "%c%c%c%c" BG_BLUE "  " RESET "%c%c%c%c%c%c    ", 201, 205, 205, 187, 186, 186, 200, 205, 205, 201, 205, 205, 188, 186, 200, 205, 205, 201, 205, 205, 188, 201, 205, 205, 205, 205, 188);
    printf(BG_WHITE_B BLACK "      @" CYAN "@@@@@@@@@@@" BLACK "#     " RESET "\n");
    printf("    " BG_WHITE_B YELLOW "%c" RED " B A C H K H O A    " YELLOW "%c" RESET "    ", 186, 186);
    printf(BG_BLUE "  " RESET "%c  " BG_BLUE "  " RESET "%c" BG_BLUE "  " RESET "%c   " BG_BLUE "  " RESET "%c   " BG_BLUE "  " RESET"%c       " BG_BLUE "     " RESET "%c    " BG_BLUE "  " RESET"%c   " BG_BLUE"  " RESET"%c   " BG_BLUE "     " RESET "%c      ", 186, 186, 186, 186, 186, 187, 186, 186, 187);
    printf(BG_WHITE_B BLACK "       @" CYAN "@@@@@@@@@" BLACK "#      " RESET"\n");
    printf("    " BG_WHITE_B YELLOW "%c" BLUE "   N @@@@@@" YELLOW "@@" BLUE "@@@@@@ " YELLOW "%c" RESET "    ", 186, 186);
    printf( BG_BLUE "  " RESET "%c  " BG_BLUE "  " RESET "%c" BG_BLUE "  " RESET "%c   " BG_BLUE "  " RESET "%c   " BG_BLUE "  " RESET"%c       %c%c%c%c%c%c    " BG_BLUE "  " RESET "%c   " BG_BLUE"  " RESET "%c   " BG_BLUE "  " RESET "%c%c%c%c      ", 186, 186, 186, 186, 186, 200, 205, 205, 205, 205, 188, 186, 186, 201, 205, 205, 188);
    printf(BG_WHITE_B BLUE "     _=======%c%c=====    " RESET "\n", 240, 240);
    printf("    " BG_WHITE_B YELLOW "%c" BLUE "   A @@@@@@@@" YELLOW "@@" BLUE "@@@@ " YELLOW "%c" RESET "    ", 186, 186);
    printf( BG_BLUE "      " RESET "%c%c%c" BG_BLUE "      " RESET "%c%c   " BG_BLUE "  " RESET "%c                 " BG_BLUE"  " RESET "%c   " BG_BLUE"  " RESET "%c   " BG_BLUE"  " RESET "%c         ", 201, 188, 200, 201, 188, 186, 186, 186, 186);
    printf(BG_WHITE_B BLUE "    //    " BLACK "@" CYAN "@@@@@" BLACK "#   " BLUE "=>  " RESET "\n");
    printf("    " BG_WHITE_B YELLOW "%c  " BLUE " N @@@@@@@@*" YELLOW "@@@" BLUE "@@ " YELLOW "%c" RESET "    ", 186, 186);
    printf("%c%c%c%c%c%c%c  %c%c%c%c%c%c%c    %c%c%c                 %c%c%c   %c%c%c   %c%c%c         ", 200, 205, 205, 205, 205, 205, 188, 200, 205, 205, 205, 205, 205, 188, 200, 205, 188, 200, 205, 188, 200, 205, 188, 200, 205, 188);
    printf(BG_WHITE_B BLUE "  <=      " BLACK"@" CYAN "@@@@" BLACK"#  " BLUE"//    " RESET "\n");
    printf("    " BG_WHITE_B YELLOW "%c" BLUE "   G @@@@@@@@" YELLOW "@@@@" BLUE "@@ " YELLOW "%c" RESET "                                                                    ", 186, 186);
    printf(BG_WHITE_B BLUE "    ========%c%c=====%c    " RESET"\n", 240, 240, 196);
    printf("    " BG_WHITE_B YELLOW "%c" BLUE "     @@@@@@@#" YELLOW "@@@@@" BLUE "@ " YELLOW "%c" RESET BOLD GREEN "                     PBL1 - Finding Shortest Path                   " RESET ,186, 186);
    printf(BG_WHITE_B BLACK "        @" CYAN "@@@@@" BLACK"#         " RESET "\n");
    printf("    " BG_WHITE_B YELLOW "%c" BLUE "     @@@@@" YELLOW "@@@@@@@" BLUE "#@ " YELLOW "%c" RESET BOLD GREEN "           Dijkstra's and Bellman-Ford Algorithm Visualizer         " RESET , 186, 186);
    printf(BG_WHITE_B BLACK "       @" CYAN "@@@@@" BLACK "#          " RESET "\n");
                printf("    " BG_WHITE_B YELLOW "%c" BLUE "     @@" YELLOW "@@@@@@@@@@" BLUE "@@ " YELLOW "%c" RESET "    Implemented by: Tran Van Tung && Hua Van Truong                 ", 186, 186);
    printf(BG_WHITE_B BLACK " ______________________ " RESET "\n");
    printf("    " BG_WHITE_B YELLOW "%c", 200);
	for(int i = 1; i < 21; i++){
		printf("%c", 205);
	}
	printf("%c" RESET "    Supervisor    : Dr. Truong Ngoc Chau                            ", 188);
    printf(BG_WHITE_B BLACK"   I T  F A C U L T Y   " RESET "\n");
    printf("\n\n\n");
}

void printWithDelay(const char *line){
    int delayPerChar = 10000;
    while(*line){
        printf("%c", *line++);
        fflush(stdout); // In ra ngay
        usleep(delayPerChar); // Delay tung ky tu
    }
}

void printMainMenu(){
    printf(BOLD WHITE BG_BLUE " MAIN MENU " RESET "\n");
    printf(CYAN);
    printWithDelay("1. Load graph from file\n");
    printWithDelay("2. Create new graph\n");
    printWithDelay("3. Run algorithm \n");
    printWithDelay("4. View result\n");
    printf(BOLD);
    printWithDelay("0. EXIT\n");
    printf(BOLD YELLOW "Your choice: " RESET);
}

void printMenuCreateGraph(){
    printBanner();
    printf(BOLD WHITE BG_BLUE  " Create new graph " RESET "\n");
    printf(CYAN);
    printWithDelay("1. Input manually\n");
    printWithDelay("2. Generate random graph\n");
    printf(BOLD);
    printWithDelay("0. Back to MAIN MENU\n");
    printf(BOLD YELLOW "Your choice: " RESET);
}

void printMenuRun(){
    printBanner();
    printf(BOLD WHITE BG_BLUE  " Run algorithm " RESET "\n");
    printf(CYAN);
    printWithDelay("1. View current graph\n");
    printWithDelay("2. Run with Dijkstra's algorithm\n");
    printWithDelay("3. Run with Bellman-Ford algorithm\n");
    printf(BOLD);
    printWithDelay("0. Back to MAIN MENU\n");
    printf(BOLD YELLOW "Your choice: " RESET);
}

void printMenuViewResult(){
    printBanner();
    printf(BOLD WHITE BG_BLUE  " View result " RESET "\n" );
    printf(CYAN);
    printWithDelay("1. Visualize graph\n");
    printWithDelay("2. View Dijkstra's algorithm steps\n");
    printWithDelay("3. View Bellman-Ford algorithm steps\n");
    printf(BOLD);
    printWithDelay("0. Back to MAIN MENU\n");
    printf(BOLD YELLOW "Your choice: " RESET);
}

void printAdjacencyMatrix(int** graph, int v){
    printf("\n" BOLD BG_MAGENTA WHITE " Adjacency Matrix " RESET "\n");
    printf("     ");
    for(int i = 1; i <= v; i++){
        printf(BOLD GREEN "%5d" RESET, i);
    }
    printf("\n");
    
    for(int i = 1; i <= v; i++){
        printf(BOLD GREEN "%5d" RESET, i);
        for(int j = 1; j <= v; j++){
            if(graph[i][j] == 0){
                printf(RED "%5d" RESET, 0);
            } 
            else{
                printf("%5d", graph[i][j]);
            }
        }
        printf("\n");
    }
}

void printAdjacencyList(Edge* adj, int v){
    printf("\n" BOLD BG_MAGENTA WHITE " Adjacency List " RESET "\n");
    for(int i = 1; i <= v; i++){
        printf(CYAN "[%d]" RESET " -> { ", i);
        Edge current = adj[i];
        while(current != NULL){
            printf(CYAN "%d" RESET "(%d); ", current->v, current->w);
            current = current->next;
        }
        printf("}\n");
    }
}

void freeMemory(int*** graph, Edge** adj, int** path, int* npath, int v){
    if(*graph != NULL){
        for(int i = 0; i <= v; i++){
            free((*graph)[i]);
        }
        free(*graph);
        *graph = NULL; 
    }
    
    if(*adj != NULL){
        for(int i = 1; i <= v; i++){
            Edge temp = (*adj)[i];
            while(temp){
                Edge next = temp->next;
                free(temp);
                temp = next;
            }
        }
        free(*adj);
        *adj = NULL;  
    }

    if(*path != NULL){
        free(*path);
        *path = NULL;  
        *npath = 0;
    }
}

void loadGraphFromFile(int *v, int ***graph, Edge **adj, int *checkNegativeWeight, int *countedge, int **path, int *npath){
    while(1){
        printBanner();
        printf(BOLD WHITE BG_BLUE  " Load Graph FromFile " RESET "\n" );
        printf(BOLD YELLOW);
        printWithDelay("Enter file name: ");
        printf(RESET);
        char fileName[100];
        scanf("%s",fileName);
        getchar();
        
        system("clear || cls");
       
        FILE* fg = fopen(fileName, "r");
        if(fg == NULL){
            printf(RED "Error: Unable to open file " YELLOW "%s" RED ". Please check if the file exists.\n" RESET, fileName);
            printf("Press Enter to return to MAIN MENU.\n");
            getchar();
            break;
        }
        // lam sach truoc khi load do thi moi
        freeMemory(graph, adj, path, npath, *v);
        *checkNegativeWeight = 0;
        fscanf(fg, "%d", v);
        *graph = createGraph(*v);
        for(int i = 1; i <= *v; i++){
            for(int j = 1; j <= *v; j++){
                fscanf(fg,"%d", &(*graph)[i][j]);
                if((*graph)[i][j] < 0) *checkNegativeWeight = 1;
            }
        }
        fclose(fg);

        *countedge = convertMatrixToList(*graph, adj, *v);   
        printAdjacencyMatrix(*graph, *v);
        printAdjacencyList(*adj, *v);
        printf("Press Enter to confirm.\n");
        printf("Press " YELLOW "0" RESET " to reEnter\n");
        char t; t = getchar();
        if(t == '0') continue;
        else break;
    }
    return;
}

void createNewGraph(int *v, int ***graph, Edge **adj, int *checkNegativeWeight, int *countedge, int **path, int *npath){
    printMenuCreateGraph();
    int choice2;
    int checkChoice = scanf("%d",&choice2);
    if(checkChoice == 0){
        while(getchar() != '\n');
        return;
    } 
    if(choice2 == 0) return;
        
    else if(choice2 == 1){
        //lam sach truoc khi load do thi khac
        freeMemory(graph, adj, path, npath, *v);
        *checkNegativeWeight = 0;

        printf(BOLD GREEN "Enter the number of vertices: " RESET);
        if(scanf("%d", v) == 0){
            while(getchar() != '\n');
            return;
        }

        printf(BOLD GREEN "Enter the weight matrix:\n" RESET);
        *graph = enterMatrixData(*v, checkNegativeWeight); getchar();
        *countedge = convertMatrixToList(*graph, adj, *v);

        printf(GREEN "Successfully created new graph\n" RESET);
        printf("Press Enter to continue...\n"); getchar();
    }
    else if(choice2 == 2){
        while(1){
            //lam sach truoc khi load do thi khac
            freeMemory(graph, adj, path, npath, *v);
            *checkNegativeWeight = 0;

            printf(BOLD GREEN "Enter the number of vertices: " RESET);
            if(scanf("%d",v) == 0){
                while(getchar() != '\n');
                return;
            }
            getchar();
            srand(time(NULL));
            *graph = randomGraph(*v);
            if(*graph == NULL) continue;
            *countedge = convertMatrixToList(*graph, adj, *v);
            system("clear || cls");
            printAdjacencyMatrix(*graph, *v);
            printAdjacencyList(*adj, *v);
            printf("Press Enter to confirm\n");
            printf("Press " YELLOW "0" RESET " to randomize again\n");
            char t; t = getchar();
            if(t == '0') continue;
            else break;
        }
    }
    return;
}

void runAlgorithm(int v, int **graph, Edge *adj, int checkNegativeWeight, int countedge, int *begin, int *end, int **path, int *npath){
    if(graph == NULL){
        printf(RED "Warning! No graph has been loaded!\n" RESET);
        printf("Press Enter to return to the MAIN MENU...\n"); getchar(); getchar();
        return;
    }
    while(1){
        printMenuRun();
        int choiceRun;
        int checkChoice = scanf("%d",&choiceRun);
        if(checkChoice == 0){
            while(getchar() != '\n');
            continue;
        } 
        if(choiceRun == 0) return;
        else if(choiceRun == 1){
            system("clear || cls");
            printAdjacencyMatrix(graph, v);
            printAdjacencyList(adj, v);
            printf("Press Enter to continue..."); getchar(); getchar();
        }
        else if(choiceRun == 2){
            if(checkNegativeWeight){
                printf(RED "Warning... the graph contains negative weights!\n" RESET);
                printf("Press Enter to continue...\n"); getchar(); getchar();
            }
            if(*path != NULL){
                free(*path);
                *path = NULL;
            }
            *path = (int*)malloc(sizeof(int) * (v + 1));
            if((*path) == NULL) {
                printf(RED "Memory allocation error!\n" RESET);
                exit(1); 
            }

            printf("Enter the start and end vertices (range: " YELLOW "1" RESET " to " YELLOW "%d" RESET "): ", v);
            scanf("%d%d", begin, end);
            if (*begin < 1 || *begin > v || *end < 1 || *end > v) {
                printf(RED "Invalid start or end vertex!\n" RESET);
                printf("Press Enter to continue..."); getchar(); getchar();
                continue;
            }
            dijkstra(v, adj, *begin, *end, *path, npath, countedge);
            printf("Press Enter to continue..."); getchar(); getchar();
        }
        else if(choiceRun == 3){
            if(*path != NULL){
                free(*path);
                *path = NULL;
            } 
            *path = (int*)malloc(sizeof(int) * (v + 1));
            if((*path) == NULL) {
                printf(RED "Memory allocation error!\n" RESET);
                exit(1); 
            }

            printf("Enter the start and end vertices (range: " YELLOW "1" RESET " to " YELLOW "%d" RESET "): ", v);
            scanf("%d%d", begin, end);
            if (*begin < 1 || *begin > v || *end < 1 || *end > v) {
                printf(RED "Invalid start or end vertex!\n" RESET);
                printf("Press Enter to continue..."); getchar(); getchar();
                continue;
            }
            Bellman_Ford(v, adj, *begin, *end, *path, npath);
            printf("Press Enter to continue..."); getchar(); getchar();
        }
        else continue;
    }
}

void viewResult(int v, Edge *adj, int *path, int npath){
    printMenuViewResult();
    int choice4;
    int checkChoice = scanf("%d", &choice4);
    if(checkChoice == 0){
        while(getchar() != '\n');
        return;
    } 
    if(choice4 == 0) return;
    else if(choice4 == 1){
        exportGraphviz(adj, v, path, npath);
        printf("Press Enter to continue..."); getchar(); getchar();
    }
    else if(choice4 == 2){
        system("powershell.exe start outpDijkstra.txt");
        printf("Press Enter to continue..."); getchar(); getchar();
    }
    else if(choice4 == 3){
        system("powershell.exe start outpBellman_Ford.txt");
        printf("Press Enter to continue..."); getchar(); getchar();
    }
    return;
}
