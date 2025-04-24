#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct elementType{
    char c;
} element;

typedef struct stackinfo{
    int capacicty;
    int top;
    element *stack_array;
} *stack;

stack create(int capacity ){
    stack new_stack = (stack)malloc(sizeof(struct stackinfo));
    new_stack->stack_array  = (struct elementType*)malloc(capacity*sizeof(struct elementType));
    new_stack->capacicty = capacity;
    new_stack->top = -1;
}

int isempty(stack s){
    return s->top == -1;
}

int isfull(stack s){
    return s->top == s->capacicty-1;
}

void push(stack s, element e){
    if(isfull(s)){
        printf("the stack is full !\n");
        return;
    }
    s->top++;
    s->stack_array[s->top] = e;
    return;
}

element* pop(stack s){
    if(isempty(s)){
        printf("the stack is empty!!\n");
        return NULL;
    }
    return &s->stack_array[(s->top)--];
}
element* top(stack s){
    if(isempty(s)){
        printf("the stack is empty!!\n");
        return NULL;
    }
    return &s->stack_array[(s->top)];
}

int main(){
    stack S = create(100);
    element *e, e1;
    char s[] = "(x+3y-{(+5}+6[(uti)])";
    int n = strlen(s);
    for(int i=0; i<n; i++){
        if(s[i] == '(' || s[i] == '{' || s[i] == '['){
            e1.c = s[i];
            push(S, e1); 
        }
        else if(s[i] == ']' || s[i] == '}' || s[i] == ')'){
            if(isempty(S)){
                printf("Unbalanced!!\n");
                return 0;
            }
            if((s[i] == ')' && top(S)->c == '(') || (s[i] == '}' && top(S)->c == '{') || (s[i] == ']' && top(S)->c == '[')){
                pop(S);
            }
        }
    }
    if(isempty(S)){
        printf("Balanced..\n");
    }
    else printf("Unbalanced!\n");

    return 0;

}

