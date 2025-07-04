#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>

typedef struct stackinfo {
    int capacity ;
    int top;
    int* stackArr;
} *stack;

stack create(int capacity){
    stack S = (stack)malloc(sizeof(struct stackinfo));
    if(S == NULL){
        return NULL;
    }
    S->stackArr = (int*)malloc(sizeof(int) * capacity);
    if(S->stackArr == NULL){
        return NULL;
    }
    S->capacity = capacity;
    S->top = -1;
    return S;
}

int isEmpty(stack S){
    return S->top == -1;
}

int isFull(stack S){
    return S->top == S->capacity-1;
}

void push(stack S, int c){
    if(isFull(S)){
        printf("The stack is full already!\n");
        return;
    }
    S->top++;
    S->stackArr[S->top] = c;
    return;
}

int pop(stack S){
    if(isEmpty(S)){
        printf("The stack is empty already!\n");
        return -999;
    }
    int t = S->stackArr[S->top];
    S->top--;
    return t;
}
int top(stack S){
    if(isEmpty(S)){
        printf("The stack is empty already!\n");
        return -999;
    }
    int t = S->stackArr[S->top];
    return t;
}

int main(){
    stack S = create(1000);
    char infix[100], postfix[100] = "";
    fgets(infix, 100, stdin);
    printf("infix: %s", infix);

    infix[strcspn(infix, "\n")] = '\0'; // bo \n

    int pri[256] = {0};
    pri['*'] = 2;
    pri['/'] = 2;
    pri['+'] = 1;
    pri['-'] = 1;

    char *tok = strtok(infix, " ");
    while( tok != NULL){
        if(strcmp(tok, "(") == 0){
            push(S, '(');
        }
        else if(strcmp(tok, ")") == 0){
            while(top(S) != '('){
                char c = pop(S);
                char tmp[2] =  {c, '\0'};
                strcat(postfix, tmp);
                strcat(postfix, " ");
            }
            pop(S);
        }
        else if(isdigit(tok[0])){
            strcat(postfix, tok);
            strcat(postfix, " ");
        }
        else{
            while(!isEmpty(S) && top(S) != '(' && pri[(int)top(S)] >= pri[tok[0]]){
                char c = pop(S);
                char tmp[2] = {c, '\0'};
                strcat(postfix, tmp);
                strcat(postfix, " ");
            }
            push(S, tok[0]);
        }
        tok = strtok(NULL, " ");
    }
    while(!isEmpty(S)){
        char c = pop(S);
        char tmp[2] = {c, '\0'};
        strcat(postfix, tmp);
        strcat(postfix, " ");
    }
    printf("postfix: %s\n", postfix);

    // tinh ket qua
    strcat(postfix, "\0");
    tok = strtok(postfix, " ");
    while(tok != NULL){
        if(strcmp(tok, "+") == 0 || strcmp(tok, "-") == 0 || strcmp(tok, "*") == 0 || strcmp(tok, "/") == 0){
            int a = pop(S);
            int b = pop(S);
            if(strcmp(tok, "+") == 0){
                push(S, b + a);
            }
            else if(strcmp(tok, "-") == 0){
                push(S, b - a);
            }
            else if(strcmp(tok, "*") == 0){
                push(S, b * a);
            }
            else if(strcmp(tok, "/") == 0){
                push(S, b / a);
            }
        }
        else{
            int t = atoi(tok);
            push(S, t);
        }
        tok = strtok(NULL, " ");
    }
    printf("result: S = %d\n",pop(S));

    return 0;
}