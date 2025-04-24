#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct stackinfo{
    int capacity;
    int top;
    int* c;
};

typedef struct stackinfo *stack;

stack create(int capacity){
    stack S = (stack)malloc(sizeof(struct stackinfo));
    if(S==NULL) return NULL;
    S->top = -1;
    S->capacity = capacity;
    S->c= (int*)malloc(capacity*sizeof(int));
    if(S->c == NULL) return NULL;
    return S;
}

int isempty(stack S){
    return S->top == -1;
}

int isfull(stack S){
    return S->top == S->capacity-1;
}

void push(stack S,int c){
    if(isfull(S)){
        printf("the stack is full already !\n");
        return;
    }
    S->top++;
    S->c[S->top] = c;
}

int top(stack S){
    if(isempty(S)){
        printf("the stack is empty !\n");
        return -1;
    }
    return S->c[S->top];
}


int pop(stack S){
    if(isempty(S)){
        printf("the stack is empty !\n");
        return -1;
    }
    return S->c[S->top--];
}

int main(){
   
    stack S = create(100);
    char str[] = "1 2 3 * + 4 5 * 6 + 7 * +";
    char *token = strtok(str, " ");
    while(token != NULL){
        
        if(strcmp(token,"+") == 0 || strcmp(token,"*") == 0){
            int a = pop(S);
            int b = pop(S);
            if(strcmp(token,"+") == 0){
                push(S, a+b);
            }
            else 
                push(S,a*b);
        }
        else {
            int t = atoi(token);
            push(S, t);
        }
        token = strtok(NULL, " ");
    }
    printf("ket qua la: %d\n",pop(S) );  
    return 0;
}
