#include <stdio.h>
#include <stdlib.h>

struct elementType{
    int key;
    char *name;
};

struct nodeInfo{
    struct elementType e;
    struct nodeInfo *next;
};

typedef struct nodeInfo *node;

struct hashTable{
    int capacity;
    node *data;
};
typedef struct hashTable *HashTable;

HashTable create(int capacity){
    HashTable H = (HashTable)malloc(sizeof(struct hashTable));   
    if(H == NULL) return NULL;
    H->capacity = capacity;
    H->data = (node*)malloc(sizeof(struct nodeInfo)*capacity);
    if(H->data == NULL) return NULL;
    for(int i = 0; i<capacity; i++){
        H->data[i] = NULL;
    }
    return H;
}

int HashFunction(int key, HashTable H){
    return key % H->capacity;
}

void insert(HashTable H, struct elementType e){
    node newElement = (node)malloc(sizeof(struct nodeInfo));
    newElement->e = e;
    int pos = HashFunction(e.key,H);
    newElement->next = H->data[pos];
    H->data[pos] = newElement;
}

void showHashTable(HashTable H){
    for(int i = 0; i < H->capacity; i++){
        node tmp = H->data[i];
        while(tmp){
            printf("key: %d\tname: %s\n", tmp->e.key, tmp->e.name);
            tmp = tmp->next;
        }
    }
}

int main(){
    HashTable H = create(8);
    struct elementType e1, e2, e3, e4;
    e1.key = 1234; e1.name = "NVA";
    e2.key = 464533; e2.name = "NVB";
    e3.key = 86894; e3.name = "TVT";
    e4.key = 780948; e4.name = "LVT";

    insert(H, e1);
    insert(H, e2);
    insert(H, e3);
    insert(H, e4);
    showHashTable(H);
}