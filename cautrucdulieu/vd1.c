#include<stdio.h>
#include<stdlib.h>
struct Symbol{
    char *name;
    unsigned long val;
};

struct node {
    struct node *next;
    struct Symbol *element;
};

int main(){
    struct Symbol oneSym;
    struct Symbol twoSym;
    struct Symbol threeSym;

    oneSym.name = "One"; oneSym.val = 1;
    twoSym.name = "Two"; twoSym.val = 2;
    threeSym.name = "Three"; threeSym.val = 3;

    struct node *nodeA;
    struct node *nodeB;
    struct node *nodeC;
    struct node *nodeP;

    nodeA =(struct node*) malloc(sizeof(struct node));
    nodeB =(struct node*) malloc(sizeof(struct node));
    nodeC =(struct node*) malloc(sizeof(struct node));

    nodeA->element = &oneSym; nodeA->next = nodeB;
    nodeB->element = &twoSym; nodeB->next = nodeC;
    nodeC->element = &threeSym; nodeC->next = NULL;

    nodeP = nodeA;

    while(nodeP != NULL){
        printf("name: %s    value: %lu\n",nodeP->element->name, nodeP->element->val);
        nodeP = nodeP->next;
    }

    return 0;
}