#include<stdio.h>
int V=1;

#define INF 9999

void dijkstra(int graph[V][V], int src) {
    int L[V], visited[V];
    for (int i = 0; i < V; i++){
        visited[i] = 0;
        L[i] = INF;
    }     
        L[src] = 0;    
        for (int count = 0; count < V - 1; count++) {        
            int u = minDistance(L, visited);        
            visited[u] = 1;        
            for (int v = 0; v < V; v++)            
            if (!visited[v] && graph[u][v] && L[u] + graph[u][v] < L[v])                
            L[v] = L[u] + graph[u][v];    
        }
    }


