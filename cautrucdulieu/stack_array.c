#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct element{
    int i;
    char* name;
    
};

struct stackinfo{
    int capacity;
    int top;
    struct element *stackarray;
};

typedef struct stackinfo *stack;

stack create(int capacity){
    stack S = (stack)malloc(sizeof(struct stackinfo));
    if(S==NULL) return NULL;
    S->top = -1;
    S->capacity = capacity;
    S->stackarray = (struct element*)malloc(capacity*sizeof(struct element));
    if(S->stackarray == NULL) return NULL;
    return S;
}

int isempty(stack S){
    return S->top == -1;
}

int isfull(stack S){
    return S->top == S->capacity-1;
}

void push(stack S, struct element e){
    if(isfull(S)){
        printf("the stack is full already !\n");
        return;
    }
    S->top++;
    S->stackarray[S->top] = e;
}

struct element* top(stack S){
    if(isempty(S)){
        printf("the stack is empty !\n");
        return NULL;
    }
    return &S->stackarray[S->top];
}


struct element* pop(stack S){
    if(isempty(S)){
        printf("the stack is empty !\n");
        return NULL;
    }
    return &S->stackarray[S->top--];
}

int main(){

    stack S = create(100);
    struct element *e, e1, e2, e3;
    e1.i = 1; e1.name = "NVA";
    e2.i = 2; e2.name = "NVB";
    e3.i = 3; e3.name = "NVC";

    push(S, e1);
    push(S, e2);
    push(S, e3);

    e = pop(S);
    printf("id: %d\tname: %s\n",e->i, e->name);
    e = pop(S);
    printf("id: %d\tname: %s\n",e->i, e->name);
    e = pop(S);
    printf("id: %d\tname: %s\n",e->i, e->name);
    
    return 0;
}
