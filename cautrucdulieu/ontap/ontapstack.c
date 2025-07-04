#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct stackInfo{
    int capacity;
    int top;
    char* stackArr;
};
typedef struct stackInfo *stack;

stack create(int capacity){
    stack S = (stack)malloc(sizeof(struct stackInfo));
    if(S == NULL) return NULL;
    S->capacity = capacity;
    S->top = -1;
    S->stackArr = (char*)malloc(sizeof(char) * capacity);
    if(S->stackArr == NULL) return NULL;
    return S;
}

int isEmpty(stack S){
    return S->top == -1;
}
int isFull(stack S){
    return S->top == S->capacity-1;
}

void push(stack S, char c){
    if(isFull(S)){
        printf("the stack is full already !\n");
        return;
    }
    S->top++;
    S->stackArr[S->top] = c;
}

char pop(stack S){
    if(isEmpty(S)){
        printf("the stack is empty already !\n");
        return '#';
    }
    char c = S->stackArr[S->top];
    S->top--;
    return c;
}

char top(stack S){
    if(isEmpty(S)){
        printf("the stack is empty already !\n");
        return '#';
    }
    char c = S->stackArr[S->top];
    return c;
}

int main(){
    stack S = create(5);
    push(S, 't');
    push(S, 'u');
    push(S, 'n');
    push(S, 'g');
    push(S, '2');
    push(S, '1');
    while(!isEmpty(S)){
        printf("%c ", pop(S));
    }
    printf("\n");

    pop(S);

    char str[] =  "(x+12-{4-7]]]}+8+y*[x-5])";
    int n = strlen(str);
    for(int i = 0; i<n; i++){
        int c = str[i];
        if(c == '(' || c == '{' || c == '[') push(S, c);
        else if(c == ')' || c == '}' || c == ']'){
            if(isEmpty(S)){
                printf("Unbalanced!\n");
                return 0;
            }
            else if((c == ')' && top(S) == '(') || (c=='}' && top(S) == '{') || (c == ']' && top(S) == '[')){
                pop(S);
            }
            else{
                printf("Unbalanced!!\n");
                return 0;
            }
        }
    }
    if(isEmpty(S)){
        printf("Balanced!\n");
    }
    else printf("Unbalanced!\n");
    return 0;
}