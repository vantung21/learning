#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>

struct stackinfo{
    int capacity;
    int top;
    char* c;
};

typedef struct stackinfo *stack;

stack create(int capacity){
    stack S = (stack)malloc(sizeof(struct stackinfo));
    if(S==NULL) return NULL;
    S->top = -1;
    S->capacity = capacity;
    S->c= (char*)malloc(capacity*sizeof(char));
    if(S->c == NULL) return NULL;
    return S;
}

int isempty(stack S){
    return S->top == -1;
}

int isfull(stack S){
    return S->top == S->capacity-1;
}

void push(stack S,char c){
    if(isfull(S)){
        printf("the stack is full already !\n");
        return;
    }
    S->top++;
    S->c[S->top] = c;
}

char top(stack S){
    if(isempty(S)){
        printf("the stack is empty !\n");
        return -1;
    }
    return S->c[S->top];
}


char pop(stack S){
    if(isempty(S)){
        printf("the stack is empty !\n");
        return -1;
    }
    return S->c[S->top--];
}

int main(){
    stack st = create(100);
    char c[] = "1+2*3+(4*5+6)*7";
    char kq[1000];
    int pri[256];
    pri['*'] = 2;
    pri['/'] = 2;
    pri['+'] = 1;
    pri['-'] = 1;
    pri['('] = 0;
    pri[')'] = 0;

    int cnt = 0;
    int length = strlen(c);
    for(int i = 0; i< length; i++){
        if(c[i] == '('){
            push(st, c[i]);
        }
        else if(c[i] == ')'){
            while(!isempty(st) && top(st) != '('){
                kq[cnt++] = pop(st);
            }
            pop(st);
        }
        else if(isdigit(c[i])){
            kq[cnt++] = c[i];
        }
        else{
            while(!isempty(st) && top(st) != '(' && pri[top(st)] >= pri[c[i]]){
                kq[cnt++] = pop(st);
            }
            push(st, c[i]);
        }
    }
    while(!isempty(st)){
        kq[cnt++] = pop(st);
    }
    kq[cnt] = '\0';
    printf("%s\n", kq);

    
    return 0;
}
