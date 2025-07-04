#include <stdio.h>
#include <stdlib.h>

#define table_size 10

int h(int key){
    return key % table_size;
}

typedef struct elementType{
    int key;
    char *name;
    struct elementType *next;
}*element;

void insert(element T[], element e){
    int i = h(e->key);
    element newNode = (element)malloc(sizeof(struct elementType));
    newNode->key = e->key;
    newNode->name = e->name;
    newNode->next = T[i];
    T[i] = newNode;
}

element search(element T[], int key){
    int i = h(key);
    element current = T[i];
    while(current){
        if(current->key == key){
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void deleteElement(element T[], int key){
    int i = h(key);
    element current = T[i];
    element prev = NULL;
    while(current){
        if(current->key == key){
            if(prev != NULL) prev->next = current->next;
            else T[i]->next = current->next;
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

void display(element T[]){
    for(int i = 0; i<table_size; i++){
        element current = T[i];
        while(current){
            printf("key: %d\tname: %s\n", current->key, current->name);
            current = current->next;
        }
    }
}

int main(){
    element T[table_size]; 
    for(int i = 0; i<table_size; i++){
        T[i] = NULL;
    }
    struct elementType e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14;
    e1.key = 126543; e1.name = "NguyenvanA";
    e2.key = 45623; e2.name = "NguyenVanB";
    e3.key = 34342123; e3.name = "TranVanC";

    insert(T, &e1);
    insert(T, &e2);
    insert(T, &e3);

    display(T);
    element a = search(T, 34342123);
    printf("%s\n",a->name);

}