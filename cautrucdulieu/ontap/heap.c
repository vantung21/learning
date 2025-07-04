#include <stdio.h>
#include <stdlib.h>

#define maxArr 1e6

struct heapInfo{
    int capacity;
    int heap_size;
    int *heap_Arr;
};
typedef struct heapInfo *heap;

heap create(int capacity, int data[]){
    heap H = (heap)malloc(sizeof(struct heapInfo));
    if(H == NULL) return NULL;
    H->capacity = capacity;
    H->heap_size = capacity;
    H->heap_Arr = (int*)malloc(sizeof(int)*(maxArr));
    if(H->heap_Arr == NULL) return NULL;
    for(int i=1; i<=capacity; i++){
        H->heap_Arr[i] = data[i];
    }
    return H;
}

void max_heapify(heap H, int i){
    int l = 2*i;
    int r = 2*i + 1;
    int largest = i;
    if(l<= H->heap_size && H->heap_Arr[l] > H->heap_Arr[largest]) largest = l;
    if(r<= H->heap_size && H->heap_Arr[r] > H->heap_Arr[largest]) largest = r;
    if(largest != i){
        int tmp = H->heap_Arr[i];
        H->heap_Arr[i] = H->heap_Arr[largest];
        H->heap_Arr[largest] = tmp;
        max_heapify(H, largest);
    }
}

void build_maxHeap(heap H){
    H->heap_size = H->capacity;
    for(int i = H->heap_size/2; i>=1; i--){
        max_heapify(H, i);
    }
}

void heap_sort(heap H){
    build_maxHeap(H);
    for(int i=H->heap_size; i>1; i--){
        int tmp = H->heap_Arr[i];
        H->heap_Arr[i] = H->heap_Arr[1];
        H->heap_Arr[1] = tmp;
        H->heap_size--;
        max_heapify(H, 1);
    }
}

int heap_maximum(heap H){
    return H->heap_Arr[1];
}

int heap_extract_max(heap H){
    if(H->heap_size <1){
        printf("the heap is underflow!\n");
        return -999;
    }
    int max = H->heap_Arr[1];
    H->heap_Arr[1] = H->heap_Arr[H->heap_size];
    H->heap_size--;
    max_heapify(H, 1);
    return max;
}

void heap_increaKey(heap H, int i, int key){
    if(key < H->heap_Arr[i]){
        printf("the new key is smaller than the current key!\n");
        return;
    }
    H->heap_Arr[i] = key;
    while(i>1 && H->heap_Arr[i] > H->heap_Arr[i/2]){
        int t = H->heap_Arr[i];
        H->heap_Arr[i] = H->heap_Arr[i/2];
        H->heap_Arr[i/2] = t;
        i = i/2;
    }
}

void heap_insert(heap H, int key){
    if(H->heap_size < H->capacity){
        H->heap_size++;
        H->heap_Arr[H->heap_size] = key-1;
        heap_increaKey(H,H->heap_size, key);
    }
    else{
        H->capacity++;
        H->heap_size++;
        H->heap_Arr[H->heap_size] = key-1;
        heap_increaKey(H,H->heap_size, key);
    }
}

void show_heap(heap H){
    for(int i = 1; i<= H->heap_size; i++){
        printf("%d ",H->heap_Arr[i]);
    }
    printf("\n");
}
void show_arr(heap H){
    for(int i = 1; i<= H->capacity; i++){
        printf("%d ",H->heap_Arr[i]);
    }
    printf("\n");
}

int main(){
    int data[] = {0, 16, 4, 10, 12, 46, 34, 7};
    int n = sizeof(data)/sizeof(data[0])-1;
    heap H = create(n, data);
    show_heap(H);
    max_heapify(H, 3);
    show_heap(H);

    build_maxHeap(H);
    show_heap(H);

    heap_sort(H);
    show_arr(H);
    show_heap(H);

    heap_insert(H, 99);
    show_heap(H);
    show_arr(H);
    heap_insert(H, 98);
    show_heap(H);
   
    
    return 0;
}