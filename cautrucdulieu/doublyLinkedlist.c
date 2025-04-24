#include<stdio.h>
#include<stdlib.h>

#define FALSE 0
#define TRUE 1

typedef struct elementType{
    int ID;
    char* name;
}elementType;

typedef struct node{
    struct node* next;
    struct node* prev;
    elementType e;
}*list;
typedef struct node *position;

list createlist(){
    position headerNode = (position)malloc(sizeof(struct node));
    if(headerNode == NULL) return NULL;
    headerNode->next = NULL;
    headerNode->prev = NULL;
    return headerNode;
}

int insert(list pl, elementType e, position p){
    if(p == NULL){
        p = pl;
    }

    position newNode = (position)malloc(sizeof(struct node));
    if(newNode == NULL) return FALSE;

    newNode->e = e;

    newNode->next = p->next;
    newNode->prev = p;
    p->next = newNode;
    if(newNode->next != NULL)
    newNode->next->prev = newNode;
    return TRUE;
}

void del(position p){
    if(p == NULL)
    return;
    p->prev->next = p->next;
    if(p->next != NULL)
    p->next->prev = p->prev;
    return;
}

void show(list pl){
    pl = pl->next;
    while(pl != NULL){
        printf("ID: %d\tname: %s\n",pl->e.ID,pl->e.name);
        pl = pl->next;
    }
}

position findByID(list pl, int ID){
    pl = pl->next;
    while(pl != NULL && pl->e.ID != ID){
        pl = pl->next;
    }
    return pl;
}

int main(){
    list stdlist = createlist();

    elementType e1, e2, e3, e4;
    e1.ID = 1; e1.name = "Nguyen Van A";
    e2.ID = 2; e2.name = "Nguyen Van B";
    e3.ID = 3; e3.name = "Nguyen Van C";
    e4.ID = 4; e4.name = "Nguyen Van D";

    insert(stdlist,e3, NULL);
    insert(stdlist, e2, NULL);
    insert(stdlist, e1, NULL);

    printf("the list is: \n");
    show(stdlist);

    position p = findByID(stdlist, 3);
    insert(stdlist, e4, p);

    printf("the list after insert e4 is:\n");
    show(stdlist);


    return 0;
}