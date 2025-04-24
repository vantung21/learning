#include<stdio.h>
#include<stdlib.h>

#define false 0
#define true 1

struct ElementType{
    unsigned long ID;
    char *Name;
};

struct ListInfo{
    struct ElementType *TheArray;
    unsigned long count;
    unsigned long capacity;
};

typedef struct ListInfo *List;
typedef int Position;

//tao list
List createList(unsigned long capacity){
    List NewList =malloc(sizeof (struct ListInfo)); 
    NewList->TheArray = malloc(capacity*sizeof(struct ElementType));
    if(NewList -> TheArray == NULL){
        return NULL;
    }
    NewList ->count = 0;
    NewList -> capacity = capacity;
    return NewList;
}

//chen phan tu
int insert(List L,struct ElementType e, Position p){
    if(p > L->count || L->count == L->capacity)
    return false;
    Position current = L->count;
    while(current !=p){
        L->TheArray[current] = L->TheArray[current-1];
        current--;
    }
    L->TheArray[p] = e;
    L->count++;
    return true;
}

void show(List L){
    unsigned long i;
    for(i=0; i<L->count; i++){
        printf("ID: %lu         Name: %s\n",L->TheArray[i].ID, L->TheArray[i].Name);
    }
}

void del(List L, Position p){
    if(p >= L->count){
        return;
    }
    while(p<L->count-1){
        L->TheArray[p] = L->TheArray[p+1];
        p++;
    }
    L->count--;
}

int main(){
    List lststudent = createList(100);

    struct ElementType e1, e2, e3;
    e1.ID = 1; e1.Name = "Nguyen Van A";
    e2.ID = 2; e2.Name = "Nguyen Van B";
    e3.ID = 3; e3.Name = "Nguyen Van C";

    insert (lststudent, e1, 0);
    insert (lststudent, e2, 1);
    insert(lststudent, e3, 2);

    printf("the list is:\n");
    show(lststudent);

    del(lststudent, 0);
    printf("the list after delete: \n");
    show(lststudent);

    return 0;
}