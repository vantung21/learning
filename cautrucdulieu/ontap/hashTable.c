#include <stdio.h>
#include <stdlib.h>

struct element{
    int key;
    char* name;
};
struct nodeInfo{
    struct element e;
    struct nodeInfo* next;
};
typedef struct nodeInfo *node;

struct hashTable{
    int capacity;
    node* data;
};
typedef struct hashTable *HashTable;

HashTable create(int capacity){
    HashTable T = (HashTable)malloc(sizeof(struct hashTable));
    T->capacity = capacity;
    T->data = (node*)malloc(sizeof(node)*capacity);
    for(int i = 0; i < capacity; i++){
        T->data[i] = NULL;
    }
    return T;
}

int hashFunction(HashTable T, int key){
    return key % T->capacity;
}

void insert(HashTable T, struct element e){
    node newnode = (node)malloc(sizeof(struct nodeInfo));
    newnode->e = e;
    int i = hashFunction(T, e.key);
    newnode->next = T->data[i];
    T->data[i] = newnode;
}

void delete(HashTable T, int key){
    int i = hashFunction(T, key);
    node tmp = T->data[i];
    node prev = NULL;
    while(tmp != NULL){
        if(tmp->e.key == key){
            if(prev != NULL) prev->next = tmp->next;
            else T->data[i] = tmp->next;
        }
        prev = tmp;
        tmp = tmp->next;
    }
}

void showHashTable(HashTable T){
    for(int i = 0; i< T->capacity; i++){
        node tmp = T->data[i];
        while(tmp != NULL){
            printf("key: %5d\tname: %s\n", tmp->e.key, tmp->e.name);
            tmp = tmp->next;
        }
    }
    printf("\n");
}

int main(){
    HashTable T = create(5);
    struct element e1, e2, e3, e4, e5, e6, e7, e8, e9;
    e1.key = 123; e1.name = "NVA";
    e2.key = 14635; e2.name = "NVB";
    e3.key = 3543; e3.name = "NVC";
    e4.key = 6; e4.name = "TVT";
    e5.key = 3; e5.name = "TTTT";

    insert(T, e1);
    insert(T, e2);
    insert(T, e3);
    insert(T, e4);

    showHashTable(T);
    delete(T, 123);
    showHashTable(T);
    delete(T,3543);
    showHashTable(T);
    insert(T, e5);
    showHashTable(T);
}