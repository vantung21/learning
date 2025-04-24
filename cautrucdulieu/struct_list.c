#include<stdio.h>
#include<stdlib.h>

#define false 0
#define true 1

typedef struct elementtype{
    int ID;
    char *name;
}elementtype;

struct node{
    struct node *next;
    struct elementtype e;
};

typedef struct node *list;
typedef struct node *position;

int insert(list *pl, struct elementtype e, position p){
    position newnode = (position)malloc(sizeof(struct node));
    if(newnode == NULL){
        return false;
    }
    newnode->e = e;
    
    if(*pl == NULL || p == NULL){
        newnode->next = *pl;
        *pl = newnode;
    }
    else{
        newnode->next = p->next;
        p->next = newnode;
    }
    return true;
}

void show(list pl){
    while(pl != NULL){
        printf("ID: %d\tName: %s\n",pl->e.ID,pl->e.name);
        pl=pl->next;
    }
}

position findbyID(list pl, int ID){
    while(pl != NULL && pl->e.ID != ID){
        pl = pl->next;
    }
    return pl;
}



int main(){
    list stdlist = NULL;

    elementtype e1, e2, e3, e4;
    e1.ID = 1; e1.name = "Nguyen Van A";
    e2.ID = 2; e2.name = "Nguyen Van B";
    e3.ID = 3; e3.name = "Nguyen Van C";
    e4.ID = 4; e4.name = "Nguyen Van D";

    insert(&stdlist, e3, NULL );
    insert(&stdlist, e2, NULL );
    insert(&stdlist, e1, NULL );

    printf("in list: \n");
    show(stdlist);

    position p = findbyID(stdlist, 3);
    insert(&stdlist, e4, p);

    printf("list after insert: \n");
    show(stdlist);

    return 0;
}