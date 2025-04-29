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
#define BG_WHITE_B "\x1B[107m"
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

int convertMatrixToList(int **graph, Edge **adj, int v){
    *adj = (struct edge**)malloc((v+1)*sizeof(struct edge*));
    if(!(*adj)){
        printf("Loi cap phat bo nho!\n");
        return 1;
    }
    for(int i=0; i<=v; i++){
        (*adj)[i] = NULL;
    }
    int count = 0;
    for(int i=1; i<=v; i++){
        for(int j=1; j<=v; j++){
            if(graph[i][j] != 0){
                addEdge(*adj, i, j, graph[i][j]);
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

// Bellman_Ford
void Bellman_Ford(int v, Edge *adj, int begin, int end, int *path, int *npath){
    *npath = 0;
    int *L = (int*)malloc((v+1)*sizeof(int));
    int *P = (int*)malloc((v+1)*sizeof(int));
    if(!L || !P){
        printf(RED "Loi cap phat bo nho!\n" RESET);
        exit(1);
    }
    for (int i = 1; i <= v; i++){
        L[i] = INT_MAX; P[i] = 0; 
    }
    L[begin] = 0;
    int changed;
    for(int k = 1; k < v; k++){
        changed = 0;
        for(int i = 1; i<= v; i++){
            if(L[i] == INT_MAX) continue;
            Edge temp = adj[i];
            while(temp != NULL){
                int x = temp->v;
                int w = temp->w;
                if(L[x] > L[i] + w){
                    L[x] = L[i] + w;
                    P[x] = i;
                    changed = 1;
                }
                temp = temp->next;
            }   
        }
        if(changed == 0) break;
    }
    // kiem tra chu trinh am
    if(changed == 1){
        for(int i = 1; i<= v; i++){
            Edge temp = adj[i];
            while(temp != NULL){
                int x = temp->v;
                int w = temp->w;
                if(L[x] > L[i] + w){
                    printf(RED "do thi co chu trinh am!\n" RESET);
                    free(L); free(P);
                    return;
                }
                temp = temp->next;
            }  
        }
    }    
    // khong co duong di
    if(L[end] == INT_MAX){
        printf(RED "Khong co duong di tu %d den %d\n" RESET, begin, end);
        free(L); free(P);
        return;
    }
    
    //In duong di ngan nhat
    printf(BOLD "\nTong trong so cua duong di ngan nhat (bellman_ford) tu (%d) den (%d) la: " YELLOW "%d\n" RESET, begin, end, L[end]);
    printf(BOLD "Duong di:\n" RESET);

    int p = end;
    path[(*npath)++] = p; 
    while(P[p] != 0){
        path[(*npath)++] = P[p];
        p = P[p];
    }

    for(int i = (*npath) - 1; i > 0; i--){
        printf("(" BOLD YELLOW "%d" RESET ") -> ",path[i]);
    }
    printf("(" BOLD YELLOW "%d" RESET ")\n",path[0]);   
    
    free(L); free(P);
    return;
}

//dijkstra
void dijkstra(int v, Edge *adj, int begin, int end, int *path, int *npath, int edgecount) {
    *npath = 0;
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
            int x = temp->v;
            int w = temp->w;

            if(!visited[x] && L[u] + w <L[x]){
                L[x] = L[u] + w;
                add(MH, x, L[x]);
                P[x] = u;
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
        printf(RED "Loi mo file graph!\n");
        return;
    }

    fprintf(f, "digraph G {\n");
    fprintf(f, "  layout=neato;\n");   
    fprintf(f, "  overlap=false;\n"); 
    fprintf(f, "  splines=true;\n");  
    fprintf(f, "  node [shape=circle, style=filled, fillcolor=lightblue, fontname=\"Helvetica\"];\n");
    fprintf(f, "  edge [fontname=\"Helvetica\", fontsize=10];\n");

    //tu them to mau cho cac dinh, canh
    for (int i = 0; i < npath; i++) {
        fprintf(f, "  %d [fillcolor=gold, style=\"filled,bold\", penwidth=2];\n", path[i]);
    }
    fprintf(f, "  %d [fillcolor=lightgreen, style=\"filled,bold\"];\n", path[0]);
    fprintf(f, "  %d [fillcolor=salmon, style=\"filled,bold\"];\n", path[npath-1]);

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
                fprintf(f, "  %d -> %d [label=\"%d\", color=red, penwidth=2, fontcolor=red];\n", i, dinh, w);
            else
                fprintf(f, "  %d -> %d [label=\"%d\"];\n", i, dinh, w);
            temp = temp->next;
        }
    }

    fprintf(f, "}\n");

    fclose(f);
    //printf("Xuat thanh cong ra file graph.dot!\nfdp -Tpng graph.dot -o graph.png\n");
    //system("neato -Tpng graph.dot -o graph.png && graph.png");
    system("neato -Tpng graph.dot -o graph.png && powershell.exe start graph.png");

} 

void printBanner() {
    system("clear || cls");
    printf("\t" BG_WHITE_B YELLOW "%c", 201);
	for (int i = 1; i < 21; i++){
		printf("%c", 205);
	}
	printf("%c" RESET "\t\t\t\t\t\t\t\t\t",187);
    printf(BG_WHITE_B BLACK "     \\" BLUE "#############" BLACK "/    " RESET "\n");
    printf("\t" BG_WHITE_B YELLOW "%c" BLUE "   D                " YELLOW "%c" RESET "\t\t\t\t\t\t\t\t\t", 186, 186);
    printf(BG_WHITE_B BLACK "      \\" BLUE "###########" BLACK "/     " RESET "\n");
    printf("\t" BG_WHITE_B YELLOW "%c" RED " B A C H K H O A    " YELLOW "%c" RESET "\t\t\t\t\t\t\t\t\t", 186, 186);
    printf(BG_WHITE_B BLACK "       \\" BLUE"#########" BLACK "/      " RESET"\n");
    printf("\t" BG_WHITE_B YELLOW "%c" BLUE "   N @@@@@@" YELLOW "@@" BLUE "@@@@@@ " YELLOW "%c" RESET "\t", 186, 186);
    printf(BG_BLUE "      " RESET "%c " BG_BLUE "  " RESET "%c   " BG_BLUE "  " RESET "%c" BG_BLUE "        " RESET"%c              " BG_BLUE "  " RESET"%c" BG_BLUE "        " RESET"%c" BG_BLUE "       " RESET "%c\t", 187, 187, 187, 187, 187, 187, 187);
    printf(BG_WHITE_B BLUE "     _=======%c%c=====    " RESET "\n", 240, 240);
    printf("\t" BG_WHITE_B YELLOW "%c" BLUE "   A @@@@@@@@" YELLOW "@@" BLUE "@@@@ " YELLOW "%c" RESET "\t", 186, 186);
    printf(BG_BLUE "  " RESET "%c%c%c" BG_BLUE "  " RESET "%c" BG_BLUE "  " RESET "%c   " BG_BLUE "  " RESET "%c%c%c%c" BG_BLUE "  " RESET "%c%c%c%c              " BG_BLUE "  " RESET "%c%c%c%c" BG_BLUE "  " RESET "%c%c%c%c" BG_BLUE "  " RESET "%c%c%c%c%c%c\t", 201, 205, 205, 187, 186, 186, 200, 205, 205, 201, 205, 205, 188, 186, 200, 205, 205, 201, 205, 205, 188, 201, 205, 205, 205, 205, 188);
    printf(BG_WHITE_B BLUE "    //    " BLACK "\\" BLUE "#####" BLACK "/   " BLUE "=>  " RESET "\n");
    printf("\t" BG_WHITE_B YELLOW "%c  " BLUE " N @@@@@@@@*" YELLOW "@@@" BLUE "@@ " YELLOW "%c" RESET "\t", 186, 186);
    printf(BG_BLUE "  " RESET "%c  " BG_BLUE "  " RESET "%c" BG_BLUE "  " RESET "%c   " BG_BLUE "  " RESET "%c   " BG_BLUE "  " RESET"%c       " BG_BLUE "     " RESET "%c    " BG_BLUE "  " RESET"%c   " BG_BLUE"  " RESET"%c   " BG_BLUE "     " RESET "%c\t", 186, 186, 186, 186, 186, 187, 186, 186, 187);
    printf(BG_WHITE_B BLUE "  <=      " BLACK"/" BLUE "####" BLACK"/  " BLUE"//    " RESET "\n");
    printf("\t" BG_WHITE_B YELLOW "%c" BLUE "   G @@@@@@@@" YELLOW "@@@@" BLUE "@@ " YELLOW "%c" RESET "\t", 186, 186);
    printf(BG_BLUE "  " RESET "%c  " BG_BLUE "  " RESET "%c" BG_BLUE "  " RESET "%c   " BG_BLUE "  " RESET "%c   " BG_BLUE "  " RESET"%c       %c%c%c%c%c%c    " BG_BLUE "  " RESET "%c   " BG_BLUE"  " RESET "%c   " BG_BLUE "  " RESET "%c%c%c%c\t", 186, 186, 186, 186, 186, 200, 205, 205, 205, 205, 188, 186, 186, 201, 205, 205, 188);
    printf(BG_WHITE_B BLUE "    ========%c%c=====%c    " RESET"\n", 240, 240, 196);
    printf("\t" BG_WHITE_B YELLOW "%c" BLUE "     @@@@@@@#" YELLOW "@@@@@" BLUE "@ " YELLOW "%c" RESET "\t",186, 186);
    printf(BG_BLUE "      " RESET "%c%c%c" BG_BLUE "      " RESET "%c%c   " BG_BLUE "  " RESET "%c                 " BG_BLUE"  " RESET "%c   " BG_BLUE"  " RESET "%c   " BG_BLUE"  " RESET "%c\t\t", 201, 188, 200, 201, 188, 186, 186, 186, 186);
    printf(BG_WHITE_B BLACK "        /" BLUE "#####" BLACK"/         " RESET "\n");
    printf("\t" BG_WHITE_B YELLOW "%c" BLUE "     @@@@@" YELLOW "@@@@@@@" BLUE "#@ " YELLOW "%c" RESET "\t", 186, 186);
    printf("%c%c%c%c%c%c%c  %c%c%c%c%c%c%c    %c%c%c                 %c%c%c   %c%c%c   %c%c%c\t\t", 200, 205, 205, 205, 205, 205, 188, 200, 205, 205, 205, 205, 205, 188, 200, 205, 188, 200, 205, 188, 200, 205, 188, 200, 205, 188);
    printf(BG_WHITE_B BLACK "       /" BLUE "#####" BLACK "/          " RESET "\n");
    printf("\t" BG_WHITE_B YELLOW "%c" BLUE "     @@" YELLOW "@@@@@@@@@@" BLUE "@@ " YELLOW "%c" RESET "\t\t\t\t\t\t\t\t\t", 186, 186);
    printf(BG_WHITE_B BLACK " ______________________ " RESET "\n");
    printf("\t" BG_WHITE_B YELLOW "%c", 200);
	for (int i = 1; i < 21; i++){
			printf("%c", 205);
	}
	printf("%c" RESET "\t\t\t\t\t\t\t\t\t", 188);
    printf(BG_WHITE_B BLACK"   I T  F A C U L T Y   " RESET "\n");
    printf("\n\n");
}

void printMainMenu(){
    printf(BOLD WHITE BG_BLUE " MAIN_MENU " RESET "\n");
    printf(CYAN "1. Chon do thi co san\n" RESET);
    printf(CYAN "2. Nhap do thi moi\n" RESET);
    printf(CYAN "3. Run \n" RESET);
    printf(CYAN "4. xem ket qua\n" RESET);
    printf(BOLD CYAN "0. EXIT\n" RESET);
    printf("Your choice: ");
}
void printMenuGraph(){
    printBanner();
    printf(BOLD WHITE BG_BLUE  " Chon do thi: \n" RESET);
    printf(CYAN "1. Do thi 1 " RED "(15 canh)\n" RESET);
    printf(CYAN "2. Do thi 2 " RED "(8 canh)\n" RESET);
    printf(CYAN "3. Do thi 3 " RED "(20 canh)\n" RESET);
    printf(CYAN "4. Do thi 4 " RED "(100 canh)\n" RESET);
    printf(BOLD CYAN "0. Back to MAIN MENU\n");
    printf("Your choice: ");
}
void printMenuRun(){
    printBanner();
    printf(CYAN "1. Xem lai do thi\n");
    printf(CYAN "2. Run with Dijkstra\n");
    printf(CYAN "3. Run with Bellman_Ford\n");
    printf(BOLD CYAN "0. Back to MAIN MENU\n" RESET);
    printf("Your choice: ");
}
void printMenuXemlai(){
    printBanner();
    printf(CYAN "1. Visualize graph\n");
    printf(CYAN "2. Xem cac buoc chay\n");
    printf(CYAN BOLD "0. Back to MAIN MENU\n" RESET);
    printf("Your choice: ");
}

//cap phat bo nho cho mang 
int** createGraph(int v){
    int** graph = (int**)malloc((v+1)*sizeof(int*));
    if(!graph){
        printf(BOLD RED "Loi cap phat bo nho!\n");
        exit(1);
    }
    for(int i=0; i<=v; i++){
        graph[i] = (int*)malloc((v+1)*sizeof(int));
        if (!graph[i]) {
            printf(BOLD RED "Loi cap phat bo nho!\n");
            exit(1);
        }
    }
    return graph;
}
int** NhapMatrix(int v, int *check){
    int** graph = createGraph(v);
    for(int i = 1; i<=v; i++){
        for(int j = 1; j<=v; j++){
            scanf("%d",&graph[i][j]);
            if(graph[i][j] < 0) *check = 1;
        }
    }
    return graph;
}

// ham giai phong bo nho
void freeGrap(int** graph, int v){
    for(int i = 0; i <= v; i++){
        free(graph[i]);
    }
    free(graph);
}
void freeAdj(Edge* adj, int v){
    for(int i=1; i<= v; i++){
        Edge temp = adj[i];
        while (temp) {
            Edge next = temp->next;
            free(temp);
            temp = next;
        }
    }
    free(adj);
}

int** LoadGraphFromFile(int graphchoice, int *v, int *check){
    char filename[100];
    sprintf(filename, "dothi%d.txt", graphchoice);
    FILE* fg = fopen(filename, "r");
    if (!fg) {
        printf(RED "Cannot open file %s!\n" RESET, filename);
        return NULL;
    }
    fscanf(fg, "%d", v);
    int** graph = createGraph(*v);
    for (int i = 1; i <= *v; i++){
        for (int j = 1; j <= *v; j++){
            fscanf(fg,"%d", &graph[i][j]);
            if(graph[i][j] < 0) *check = 1;
        }
    }
    fclose(fg);
    return graph;
}
void printGraphMatrix(int** graph, int v) {
    printf("\n" BOLD "Adjacency Matrix:\n" RESET);
    printf("     ");
    for (int i = 1; i <= v; i++) {
        printf(BOLD "%5d" RESET, i);
    }
    printf("\n");
    
    for (int i = 1; i <= v; i++) {
        printf(BOLD "%5d" RESET, i);
        for (int j = 1; j <= v; j++) {
            if (graph[i][j] == 0) {
                printf(RED "%5d" RESET, 0);
            } else {
                printf("%5d", graph[i][j]);
            }
        }
        printf("\n");
    }
}

void printAdjacencyList(Edge* adj, int v) {
    printf("\n" BOLD "Adjacency List:\n" RESET);
    for (int i = 1; i <= v; i++) {
        printf(CYAN "[%d]" RESET " -> { ", i);
        Edge current = adj[i];
        while (current != NULL) {
            printf(CYAN "%d" RESET "(%d); ", current->v, current->w);
            current = current->next;
        }
        printf("}\n");
    }
}


int main() {
    int v , begin , end, countedge, npath = 0, checkNegativeWeight = 0;
    int *path = NULL; 
    int** graph = NULL;
    Edge *adj = NULL;
    while(1){
        printBanner();
        printMainMenu();
        int choice;
        scanf("%d",&choice);
        if(choice == 1){
            while(1){
                printMenuGraph();
                int graphchoice;
                scanf("%d",&graphchoice);
                getchar();
                if(graphchoice == 0) break;
                system("clear || cls");

                //lam sach truoc khi load do thi khac
                if(graph != NULL){
                    freeGrap(graph, v); graph = NULL;
                } 
                if(adj != NULL){
                    freeAdj(adj, v);
                    adj == NULL;
                } 
                checkNegativeWeight = 0;

                graph = LoadGraphFromFile(graphchoice, &v, &checkNegativeWeight);
                countedge = convertMatrixToList(graph, &adj, v);   
                printGraphMatrix(graph, v);
                printAdjacencyList(adj, v);
                printf("Nhan Enter de xac nhan\n");
                printf("Nhan phim " YELLOW "0" RESET " de chon lai\n");
                char t; t = getchar();
                if(t == '0') continue;
                else break;
            }
        }
        else if(choice == 2){
            printBanner();
            //lam sach truoc khi load do thi khac
            if(graph != NULL){
                freeGrap(graph, v); graph = NULL;
            } 
            if(adj != NULL){
                freeAdj(adj, v);
                adj == NULL;
            } 
            checkNegativeWeight = 0;

            printf("Nhap so dinh cua do thi: ");
            scanf("%d",&v); getchar();
            printf("Nhap ma tran trong so: \n");
            graph = NhapMatrix(v, &checkNegativeWeight); getchar();
            countedge = convertMatrixToList(graph, &adj, v);
            printf(GREEN "Nhap thanh cong do thi moi\n" RESET);
            printf("Enter to continue...\n"); getchar(); 
        }
        else if(choice == 3){
            while(1){
                printMenuRun();
                int choiceRun;
                scanf("%d",&choiceRun);
                if(choiceRun == 0) break;
                else if(choiceRun == 1){
                    system("clear || cls");
                    printGraphMatrix(graph, v);
                    printAdjacencyList(adj, v);
                    printf("Enter to continue..."); getchar(); getchar();
                }
                else if(choiceRun == 2){
                    if(checkNegativeWeight){
                        printf(RED "Warning... do thi co trong so am!!!\n" RESET);
                        printf("Enter to continue...\n"); getchar(); getchar();
                    } 
                    
                    if(path != NULL){
                        free(path);
                        path == NULL;
                    } 
                    path = (int*)malloc(sizeof(int)*(v+1));
                    printf("Nhap dinh bat dau va dinh ket thuc (trong khoang " YELLOW "1" RESET "->" YELLOW "%d" RESET "): ",v);
                    scanf("%d%d", &begin, &end);
                    if (begin < 1 || begin > v || end < 1 || end > v) {
                        printf(RED "Dinh bat dau hoac ket thuc khong hop le!\n" RESET);
                        printf("Enter to continue..."); getchar(); getchar();
                        continue;
                    }
                    dijkstra(v, adj, begin, end, path, &npath, countedge);
                    printf("Enter to continue..."); getchar(); getchar();
                }
                else if(choiceRun == 3){
                    if(path != NULL){
                        free(path);
                        path == NULL;
                    } 
                    path = (int*)malloc(sizeof(int)*(v+1));
                    printf("Nhap dinh bat dau va dinh ket thuc (trong khoang " YELLOW "1" RESET "->" YELLOW "%d" RESET "): ",v);
                    scanf("%d%d", &begin, &end);
                    if (begin < 1 || begin > v || end < 1 || end > v) {
                        printf(RED "Dinh bat dau hoac ket thuc khong hop le!\n" RESET);
                        printf("Enter to continue..."); getchar(); getchar();
                        continue;
                    }
                    Bellman_Ford(v, adj, begin, end, path, &npath);
                    printf("Enter to continue..."); getchar(); getchar();
                }
            }
        }
        else if(choice == 4){
            printMenuXemlai();
            int choice4;
            scanf("%d", &choice4);
            if(choice4 == 0) continue;
            else if(choice4 == 1){
                xuatGraphviz(adj, v, path, npath);
                printf("Enter to continue..."); getchar(); getchar();
            }
            else if(choice4 == 2){
                system("powershell.exe start outp.txt");
                printf("Enter to continue..."); getchar(); getchar();
            }
        }
        else if(choice == 0){
            printf(BOLD GREEN "Exiting...\n");
            if(adj != NULL) freeAdj(adj, v);
            if(graph != NULL) freeGrap(graph, v);
            if(path != NULL) free(path);
            break;
        }
    }
    return 0;
}