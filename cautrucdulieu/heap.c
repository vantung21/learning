#include <stdio.h>
#include <stdlib.h>

struct heapInfo{
    int capacity;
    int heap_size;
    int *data;
};
typedef struct heapInfo *heap;

heap craete(int capacity, int data[]){
    heap H = (heap)malloc(sizeof(struct heapInfo));
    if(H == NULL) return NULL;
    H->data = (int*)malloc(sizeof(int) * (capacity + 1));
    if(H->data == NULL){
        return NULL;
    }
    for(int i = 1; i <= capacity; i++){
        H->data[i] = data[i];
    }
    H->capacity = capacity;
    H->heap_size = capacity;
    return H;
}

void max_Heapify(heap H, int i){
    int l = 2*i;
    int r = 2*i + 1;
    int largest = i;
    if(l <= H->heap_size && H->data[l] > H->data[largest]){
        largest = l;
    }
    if(r <= H->heap_size && H->data[r] > H->data[largest]){
        largest = r;
    }
    if(largest != i){
        int temp = H->data[i];
        H->data[i] = H->data[largest];
        H->data[largest] = temp;
        max_Heapify(H, largest);
    }
}

void show(heap H){
    for(int i = 1; i<= H->heap_size; i++){
        printf("%d ", H->data[i]);
    }
    printf("\n");
}

void build_maxHeap(heap H){
    H->heap_size = H->capacity;
    for(int i = H->heap_size; i >= 1 ; i--){
        max_Heapify(H, i);
    }
}

void heap_sort(heap H){
    build_maxHeap(H);
    for(int i = H->capacity; i > 1; i--){
        int temp = H->data[1];
        H->data[1] = H->data[i];
        H->data[i] = temp;
        H->heap_size--;
        max_Heapify(H,1);
    }
}

int heap_maximum(heap H){
    return H->data[1];
}

int heap_extract_max(heap H){
    if(H->heap_size < 1){
        printf("Heap underflow!\n");
        return -999999;
    }
    int max = H->data[1];
    H->data[1] = H->data[H->heap_size];
    H->heap_size--;
    max_Heapify(H, 1);
    return max;
}
void heap_increaKey(heap H, int i, int key){
    if(key < H->data[i]){
        printf("the new key is smaller than the current key!\n");
        return;
    }
    H->data[i] = key;
    while(i>1 && H->data[i] > H->data[i/2]){
        int temp = H->data[i];
        H->data[i] = H->data[i/2];
        H->data[i/2] = temp;
        i = i/2;
    }
}

void heap_insert(heap H, int key){
    H->heap_size++;
    H->data[H->heap_size] = key-1;
    heap_increaKey(H, H->heap_size, key);
}

int main(){
    int data[] = {0, 16, 4, 10, 12, 46, 34, 7};
    int n = sizeof(data)/sizeof(data[0])-1;
    heap H = craete(n, data);
    show(H);
    max_Heapify(H, 4);
    show(H);

    build_maxHeap(H);
    show(H);

    // heap_sort(H);
    // show(H);

    heap_insert(H, 99);
    show(H);
    heap_insert(H, 98);
    show(H);
   
    
    return 0;
}