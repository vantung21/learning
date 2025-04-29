#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

// Enhanced color definitions
#define COLOR_BOLD "\033[1m"
#define COLOR_RESET "\033[0m"
#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_BLUE "\033[34m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_CYAN "\033[36m"
#define COLOR_WHITE "\033[37m"
#define BG_RED "\033[41m"
#define BG_GREEN "\033[42m"
#define BG_YELLOW "\033[43m"
#define BG_BLUE "\033[44m"
#define BG_MAGENTA "\033[45m"
#define BG_CYAN "\033[46m"
#define BG_WHITE "\033[47m"

// Animation effects
#define BLINK "\033[5m"
#define REVERSE "\033[7m"

typedef struct edge {
    int v, w;
    struct edge* next;
} *Edge;

// Enhanced heap implementation
typedef struct {
    int vertex;
    int distance;
} HeapNode;

typedef struct {
    HeapNode* nodes;
    int capacity;
    int size;
} MinHeap;

MinHeap* createMinHeap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->nodes = (HeapNode*)malloc((capacity + 1) * sizeof(HeapNode));
    heap->capacity = capacity;
    heap->size = 0;
    return heap;
}

void heapifyUp(MinHeap* heap, int index) {
    while (index > 1 && heap->nodes[index/2].distance > heap->nodes[index].distance) {
        HeapNode temp = heap->nodes[index];
        heap->nodes[index] = heap->nodes[index/2];
        heap->nodes[index/2] = temp;
        index /= 2;
    }
}

void heapifyDown(MinHeap* heap, int index) {
    while (2*index <= heap->size) {
        int child = 2*index;
        if (child < heap->size && heap->nodes[child+1].distance < heap->nodes[child].distance) {
            child++;
        }
        if (heap->nodes[index].distance <= heap->nodes[child].distance) break;
        
        HeapNode temp = heap->nodes[index];
        heap->nodes[index] = heap->nodes[child];
        heap->nodes[child] = temp;
        index = child;
    }
}

void heapInsert(MinHeap* heap, int vertex, int distance) {
    if (heap->size >= heap->capacity) return;
    
    heap->size++;
    heap->nodes[heap->size].vertex = vertex;
    heap->nodes[heap->size].distance = distance;
    heapifyUp(heap, heap->size);
}

HeapNode heapExtractMin(MinHeap* heap) {
    HeapNode min = heap->nodes[1];
    heap->nodes[1] = heap->nodes[heap->size];
    heap->size--;
    heapifyDown(heap, 1);
    return min;
}

void addEdge(Edge* adj, int u, int v, int w) {
    Edge newEdge = (Edge)malloc(sizeof(struct edge));
    newEdge->v = v;
    newEdge->w = w;
    newEdge->next = adj[u];
    adj[u] = newEdge;
}

int** loadGraphFromFile(const char* filename, int* v) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf(COLOR_RED "Cannot open file %s!\n" COLOR_RESET, filename);
        return NULL;
    }

    fscanf(file, "%d", v);
    int** graph = (int**)malloc((*v + 1) * sizeof(int*));
    for (int i = 0; i <= *v; i++) {
        graph[i] = (int*)malloc((*v + 1) * sizeof(int));
    }

    for (int i = 1; i <= *v; i++) {
        for (int j = 1; j <= *v; j++) {
            fscanf(file, "%d", &graph[i][j]);
        }
    }

    fclose(file);
    return graph;
}

void printGraphMatrix(int** graph, int v) {
    printf("\n" COLOR_BOLD "Adjacency Matrix:\n" COLOR_RESET);
    printf("     ");
    for (int i = 1; i <= v; i++) {
        printf("%5d", i);
    }
    printf("\n");
    
    for (int i = 1; i <= v; i++) {
        printf("%5d", i);
        for (int j = 1; j <= v; j++) {
            if (graph[i][j] == 0) {
                printf(COLOR_RED "%5d" COLOR_RESET, 0);
            } else {
                printf("%5d", graph[i][j]);
            }
        }
        printf("\n");
    }
}

void printAdjacencyList(Edge* adj, int v) {
    printf("\n" COLOR_BOLD "Adjacency List:\n" COLOR_RESET);
    for (int i = 1; i <= v; i++) {
        printf(COLOR_CYAN "[%d]" COLOR_RESET " -> ", i);
        Edge current = adj[i];
        while (current != NULL) {
            printf("%d(%d) -> ", current->v, current->w);
            current = current->next;
        }
        printf("NULL\n");
    }
}

void dijkstra(int v, Edge* adj, int begin, int end, int* path, int* npath) {
    int* dist = (int*)malloc((v+1) * sizeof(int));
    int* prev = (int*)malloc((v+1) * sizeof(int));
    int* visited = (int*)malloc((v+1) * sizeof(int));
    
    for (int i = 1; i <= v; i++) {
        dist[i] = INT_MAX;
        prev[i] = -1;
        visited[i] = 0;
    }
    dist[begin] = 0;
    
    MinHeap* heap = createMinHeap(v);
    heapInsert(heap, begin, 0);
    
    printf(COLOR_CYAN "\nStarting Dijkstra's algorithm from %d to %d...\n" COLOR_RESET, begin, end);
    printf("Step-by-step visualization:\n");
    
    while (heap->size > 0) {
        HeapNode current = heapExtractMin(heap);
        int u = current.vertex;
        
        if (visited[u]) continue;
        visited[u] = 1;
        
        // Animation effect for current node
        printf("\n" COLOR_BOLD BG_BLUE " Processing vertex %d " COLOR_RESET "\n", u);
        
        // Print current distances
        printf("Current distances:\n");
        for (int i = 1; i <= v; i++) {
            if (dist[i] == INT_MAX) {
                printf(COLOR_RED "INF " COLOR_RESET);
            } else if (i == u) {
                printf(COLOR_BOLD BG_GREEN " %3d " COLOR_RESET, dist[i]);
            } else if (visited[i]) {
                printf(COLOR_GREEN " %3d " COLOR_RESET, dist[i]);
            } else {
                printf(" %3d ", dist[i]);
            }
        }
        printf("\n");
        
        Edge edge = adj[u];
        while (edge != NULL) {
            int alt = dist[u] + edge->w;
            if (alt < dist[edge->v]) {
                dist[edge->v] = alt;
                prev[edge->v] = u;
                heapInsert(heap, edge->v, alt);
                
                // Highlight relaxation
                printf("  Relaxing edge %d->%d: new distance = %d\n", u, edge->v, alt);
            }
            edge = edge->next;
        }
        
        // Small delay for animation effect
        usleep(300000);
    }
    
    // Reconstruct path
    *npath = 0;
    int current = end;
    while (current != -1) {
        path[(*npath)++] = current;
        current = prev[current];
    }
    
    // Print final result with animation
    printf("\n" COLOR_BOLD BG_YELLOW COLOR_RED "\n FINAL RESULT " COLOR_RESET "\n");
    printf("Shortest distance from %d to %d: " COLOR_BOLD COLOR_YELLOW "%d\n" COLOR_RESET, begin, end, dist[end]);
    printf("Path: ");
    for (int i = *npath - 1; i > 0; i--) {
        printf(COLOR_BOLD "%d" COLOR_RESET " -> ", path[i]);
        fflush(stdout);
        usleep(200000);
    }
    printf(COLOR_BOLD "%d\n\n" COLOR_RESET, path[0]);
    
    free(dist);
    free(prev);
    free(visited);
    free(heap->nodes);
    free(heap);
}

void exportGraphviz(Edge* adj, int v, int* path, int npath) {
    FILE* file = fopen("graph.dot", "w");
    if (!file) {
        printf(COLOR_RED "Error opening file!\n" COLOR_RESET);
        return;
    }
    
    fprintf(file, "digraph G {\n");
    fprintf(file, "  layout=neato;\n");
    fprintf(file, "  overlap=false;\n");
    fprintf(file, "  splines=true;\n");
    fprintf(file, "  node [shape=circle, style=filled, fillcolor=lightblue, fontname=\"Helvetica\"];\n");
    fprintf(file, "  edge [fontname=\"Helvetica\", fontsize=10];\n");
    
    // Special styling for path nodes
    for (int i = 0; i < npath; i++) {
        fprintf(file, "  %d [fillcolor=gold, style=\"filled,bold\", penwidth=2];\n", path[i]);
    }
    fprintf(file, "  %d [fillcolor=lightgreen, style=\"filled,bold\"];\n", path[0]);
    fprintf(file, "  %d [fillcolor=salmon, style=\"filled,bold\"];\n", path[npath-1]);
    
    // Add edges
    for (int i = 1; i <= v; i++) {
        Edge edge = adj[i];
        while (edge != NULL) {
            // Check if edge is in shortest path
            int inPath = 0;
            for (int j = npath - 1; j > 0; j--) {
                if (path[j] == i && path[j-1] == edge->v) {
                    inPath = 1;
                    break;
                }
            }
            
            if (inPath) {
                fprintf(file, "  %d -> %d [label=\"%d\", color=red, penwidth=2, fontcolor=red];\n", 
                       i, edge->v, edge->w);
            } else {
                fprintf(file, "  %d -> %d [label=\"%d\"];\n", i, edge->v, edge->w);
            }
            edge = edge->next;
        }
    }
    
    fprintf(file, "}\n");
    fclose(file);
    
   // printf(COLOR_GREEN "Graphviz file generated. Use this command to render:\n");
 //   printf(COLOR_BOLD "  neato -Tpng graph.dot -o graph.png && open graph.png\n" COLOR_RESET);
   // system("neato -Tpng graph.dot -o graph.png && graph.png");
   system("neato -Tpng graph.dot -o graph.png && powershell.exe start graph.png");

}

void printBanner() {
    system("clear || cls");
    printf(COLOR_BOLD COLOR_CYAN "\n");
    printf("  _____  _  _      _    _             _           _   _             \n");
    printf(" |  __ \\(_)| |    | |  | |           | |         | | (_)            \n");
    printf(" | |  | | || | __ | |__| |  ___  ___ | |_  __ _  | |_ _  ___ __ __ \n");
    printf(" | |  | | || |/ / |  __  | / _ \\/ __|| __|/ _` | | __| |/ __|\\ \\ / \n");
    printf(" | |__| | ||   <  | |  | ||  __/\\__ \\| |_| (_| | | |_| | (__  \\ V  \n");
    printf(" |_____/|_||_|\\_\\ |_|  |_| \\___||___/ \\__|\\__,_|  \\__|_|\\___|  \\_/ \n");
    printf(COLOR_RESET);
    printf(COLOR_BOLD COLOR_YELLOW "               Dijkstra Algorithm Visualizer\n\n" COLOR_RESET);
}

void showGraphMenu() {
    printf(COLOR_BOLD BG_BLUE "\n SELECT GRAPH " COLOR_RESET "\n");
    printf(COLOR_BOLD "1. Small graph (5 vertices)\n");
    printf("2. Medium graph (8 vertices)\n");
    printf("3. Large graph (10 vertices)\n");
    printf("4. Return to main menu\n" COLOR_RESET);
    printf(COLOR_YELLOW "Select option: " COLOR_RESET);
}

void mainMenu() {
    int v = 0;
    int** graph = NULL;
    Edge* adj = NULL;
    int* path = NULL;
    int npath = 0;
    
    while (1) {
        printBanner();
        printf(COLOR_BOLD BG_BLUE "\n MAIN MENU " COLOR_RESET "\n");
        printf(COLOR_BOLD "1. Load predefined graph\n");
        printf("2. Enter custom graph\n");
        printf("3. Run Dijkstra's algorithm\n");
        printf("4. Visualize graph\n");
        printf("5. Exit\n" COLOR_RESET);
        printf(COLOR_YELLOW "Select option: " COLOR_RESET);
        
        int choice;
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: {
                int graphChoice;
                do {
                    showGraphMenu();
                    scanf("%d", &graphChoice);
                    
                    const char* filename;
                    switch (graphChoice) {
                        case 1: filename = "dothi1.txt"; break;
                        case 2: filename = "dothi2.txt"; break;
                        case 3: filename = "dothi3.txt"; break;
                        case 4: continue;
                        default: 
                            printf(COLOR_RED "Invalid choice!\n" COLOR_RESET);
                            continue;
                    }
                    
                    // Free previous graph if exists
                    if (graph != NULL) {
                        for (int i = 0; i <= v; i++) free(graph[i]);
                        free(graph);
                    }
                    if (adj != NULL) {
                        for (int i = 1; i <= v; i++) {
                            Edge current = adj[i];
                            while (current != NULL) {
                                Edge next = current->next;
                                free(current);
                                current = next;
                            }
                        }
                        free(adj);
                    }
                    
                    graph = loadGraphFromFile(filename, &v);
                    if (graph == NULL) continue;
                    
                    adj = (Edge*)malloc((v + 1) * sizeof(Edge));
                    for (int i = 0; i <= v; i++) adj[i] = NULL;
                    
                    for (int i = 1; i <= v; i++) {
                        for (int j = 1; j <= v; j++) {
                            if (graph[i][j] != 0) {
                                addEdge(adj, i, j, graph[i][j]);
                            }
                        }
                    }
                    
                    printf(COLOR_GREEN "\nGraph loaded successfully!\n" COLOR_RESET);
                    printGraphMatrix(graph, v);
                    printAdjacencyList(adj, v);
                    
                } while (graphChoice != 4);
                break;
            }
            
            case 2: {
                printf("Enter number of vertices: ");
                scanf("%d", &v);
                
                // Free previous graph if exists
                if (graph != NULL) {
                    for (int i = 0; i <= v; i++) free(graph[i]);
                    free(graph);
                }
                if (adj != NULL) {
                    for (int i = 1; i <= v; i++) {
                        Edge current = adj[i];
                        while (current != NULL) {
                            Edge next = current->next;
                            free(current);
                            current = next;
                        }
                    }
                    free(adj);
                }
                
                graph = (int**)malloc((v + 1) * sizeof(int*));
                for (int i = 0; i <= v; i++) {
                    graph[i] = (int*)malloc((v + 1) * sizeof(int));
                }
                
                printf("Enter adjacency matrix (one row at a time):\n");
                for (int i = 1; i <= v; i++) {
                    printf("Row %d: ", i);
                    for (int j = 1; j <= v; j++) {
                        scanf("%d", &graph[i][j]);
                    }
                }
                
                adj = (Edge*)malloc((v + 1) * sizeof(Edge));
                for (int i = 0; i <= v; i++) adj[i] = NULL;
                
                for (int i = 1; i <= v; i++) {
                    for (int j = 1; j <= v; j++) {
                        if (graph[i][j] != 0) {
                            addEdge(adj, i, j, graph[i][j]);
                        }
                    }
                }
                
                printf(COLOR_GREEN "\nCustom graph created successfully!\n" COLOR_RESET);
                printGraphMatrix(graph, v);
                printAdjacencyList(adj, v);
                break;
            }
            
            case 3: {
                if (v == 0) {
                    printf(COLOR_RED "No graph loaded! Please load or create a graph first.\n" COLOR_RESET);
                    sleep(1);
                    break;
                }
                
                int begin, end;
                printf("Enter start vertex (1-%d): ", v);
                scanf("%d", &begin);
                printf("Enter end vertex (1-%d): ", v);
                scanf("%d", &end);
                
                if (begin < 1 || begin > v || end < 1 || end > v) {
                    printf(COLOR_RED "Invalid vertices!\n" COLOR_RESET);
                    sleep(1);
                    break;
                }
                
                if (path != NULL) free(path);
                path = (int*)malloc(v * sizeof(int));
                npath = 0;
                
                dijkstra(v, adj, begin, end, path, &npath);
                
                printf("Press Enter to continue...");
                getchar(); getchar();
                break;
            }
            
            case 4: {
                if (v == 0) {
                    printf(COLOR_RED "No graph loaded! Please load or create a graph first.\n" COLOR_RESET);
                    sleep(1);
                    break;
                }
                
                if (npath == 0) {
                    printf(COLOR_RED "No path calculated yet! Please run Dijkstra's algorithm first.\n" COLOR_RESET);
                    sleep(1);
                    break;
                }
                
                exportGraphviz(adj, v, path, npath);
                printf("Press Enter to continue...");
                getchar(); getchar();
                break;
            }
            
            case 5: {
                // Clean up
                if (graph != NULL) {
                    for (int i = 0; i <= v; i++) free(graph[i]);
                    free(graph);
                }
                if (adj != NULL) {
                    for (int i = 1; i <= v; i++) {
                        Edge current = adj[i];
                        while (current != NULL) {
                            Edge next = current->next;
                            free(current);
                            current = next;
                        }
                    }
                    free(adj);
                }
                if (path != NULL) free(path);
                
                printf(COLOR_GREEN "Exiting...\n" COLOR_RESET);
                return;
            }
            
            default: {
                printf(COLOR_RED "Invalid choice!\n" COLOR_RESET);
                sleep(1);
                break;
            }
        }
    }
}

int main() {
    mainMenu();
    return 0;
}