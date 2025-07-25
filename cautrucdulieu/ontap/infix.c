#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct stackInfo{
    int capacity;
    int top;
    int *stackArr;
};
typedef struct stackInfo *stack;

stack create(int capacity){
    stack s = (stack)malloc(sizeof(struct stackInfo));
    if(s == NULL) return NULL;
    s->top = -1;
    s->capacity = capacity;
    s->stackArr = (int*)malloc(sizeof(int)*capacity);
    if(s->stackArr == NULL) return NULL;
    return s;
}

int isEmpty(stack s){
    return s->top == -1;
}
int isFull(stack s){
    return s->top == s->capacity-1;
}

void push(stack s, int c){
    if(isFull(s)){
        printf("the stack is full already!\n");
        return;
    }
    s->top++;
    s->stackArr[s->top] = c;
}

int pop(stack s){
    if(isEmpty(s)){
        printf("the stack is empty already !\n");
        return 9999;
    }
    int c = s->stackArr[s->top];
    s->top--;
    return c;
}
int top(stack s){
    if(isEmpty(s)){
        printf("the stack is empty already !\n");
        return -9999;
    }
    int c = s->stackArr[s->top];
    return c;
}

int main(){
    stack S = create(100);
    char infix[] = "1 2 3 * + 4 5 * 6 + 7 * -";
    char *tok = strtok(infix, " ");
    while(tok != NULL){
        if(strcmp(tok, "+") == 0 || strcmp(tok, "-") == 0 || strcmp(tok, "*") == 0 || strcmp(tok, "/") == 0){
            int a = pop(S);
            int b = pop(S);
            if(strcmp(tok, "+") == 0){
                push(S, b+a);
            }
            else if(strcmp(tok, "-") == 0) push(S, b-a);
            else if(strcmp(tok, "*") == 0) push(S, b*a);
            else push(S, b/a);
        }
        else push(S, atoi(tok));
        tok = strtok(NULL, " ");
    }
    printf("ket qua: %d\n", pop(S));

    return 0;
}