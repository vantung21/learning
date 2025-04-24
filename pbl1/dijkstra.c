#include<stdio.h>
#include<limits.h>
#include<stdlib.h>

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
void dijkstra(int v,int graph[][1001], int source, int sink){
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
    int a[v+1], s=0;
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

void nhap(int graph[][1001], int v){
    printf("nhap ma tran trong so cua do thi(khong am):\n");
    for(int i=1; i<=v; i++){
        for(int j=1; j<=v; j++){
            scanf("%d",&graph[i][j]);
        }
    }

}
        
int main(){
    // freopen("inp.txt","r", stdin);
    // freopen("outp.txt", "w", stdout);
    int v;
    // nhap so luong dinh
    scanf("%d",&v);
    int graph[1001][1001];
    nhap(graph,v);
    int source, sink;
    scanf("%d%d",&source,&sink);

    dijkstra(v, graph, source, sink);

    return 0;
}