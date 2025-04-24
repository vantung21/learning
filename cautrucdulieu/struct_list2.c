#include<stdio.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct elementType{
    int ID;
    char* name;
} elementType;

typedef struct node{
    elementType e;
    struct node* next;
}*list;

typedef struct node *position;

int insert(list pl, elementType e, position p){
    list newnode = (list)malloc(sizeof(struct node));
    if(newnode == NULL){
        return FALSE;
    }

    newnode->e = e;

    if(p == NULL){
        p = pl;
    }

    newnode->next = p->next;
    p->next = newnode;
    return TRUE;
}

void show(list pl){
    pl = pl->next;
    while(pl != NULL){
        printf("ID: %d\tname: %s\n",pl->e.ID,pl->e.name);
        pl = pl->next;
    }
}

position fineByID(list pl, int ID){
    pl = pl->next;
    while(pl != NULL && pl->e.ID != ID){
        pl = pl->next;
    }
    return pl;
}

list createlist(){
    list headerNode = (list)malloc(sizeof(struct node));
    headerNode->next = NULL;
    return headerNode;
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

    position p = fineByID(stdlist, 3);
    insert(stdlist, e4, p);

    printf("the list after insert e4 is:\n");
    show(stdlist);

    return 0;
}