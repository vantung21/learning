#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
    stack st = create(100);
    char infix[] = "1 + 2 * 3 + ( 4 * 5 + 6 ) * 7";
    char postfix[100] = "";
    printf("infix: %s\n", infix);
    int pri[256] = {0};
    pri['+'] = pri['-'] = 1;
    pri['*'] = pri['/'] = 2;

    char *tok = strtok(infix, " ");
    while(tok != NULL){
        if(isdigit(tok[0])){
            strcat(postfix, tok);
            strcat(postfix, " ");
        }
        else if(strcmp(tok, "(") == 0) push(st, '(');
        else if(strcmp(tok, ")") == 0){
            while(top(st) != '('){
                char c = pop(st);
                char tmp[2] = {c, '\0'};
                strcat(postfix, tmp);
                strcat(postfix, " ");
            }
            pop(st);
        }
        else {
            while(!isEmpty(st) && pri[top(st)] >= pri[tok[0]] && strcmp(tok, "(") != 0){
                char c = pop(st);
                char tmp[2] = {c, '\0'};
                strcat(postfix, tmp);
                strcat(postfix, " ");
            }
            push(st, tok[0]);
        }
        tok = strtok(NULL, " ");
    }
    while(!isEmpty(st)){
        char c = pop(st);
        char tmp[2] = {c, '\0'};
        strcat(postfix, tmp);
        strcat(postfix, " ");
    }

    printf("postfix: %s\n", postfix);
  
    // tinh gia tri 
    tok = strtok(postfix, " ");
    while(tok != NULL){
        if(strcmp(tok, "+") == 0 || strcmp(tok, "-") == 0 || strcmp(tok, "*") == 0 || strcmp(tok, "/") == 0){
            int a = pop(st);
            int b = pop(st);
            if(strcmp(tok, "+") == 0){
                push(st, b+a);
            }
            else if(strcmp(tok, "-") == 0) push(st, b-a);
            else if(strcmp(tok, "*") == 0) push(st, b*a);
            else push(st, b/a);
        }
        else push(st, atoi(tok));
        tok = strtok(NULL, " ");
    }
    printf("ket qua: %d\n", pop(st));
}