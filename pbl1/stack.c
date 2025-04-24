#include<stdio.h>
#include<string.h>

#define MAX 1000
char stack_arr[MAX];
int top =-1;

int isfull(){
    if(top == MAX-1) return 1;
    return 0;
}

int isempty(){
    if(top ==-1){
        return 1;
    }
    return 0;
}

void push(char data){
    if(isfull()){
        printf("stack is full...\n");
        return;
    }
    stack_arr[++top] = data;
}

int pop(){
    if(isempty()){
        printf("stack is empty...\n");
        return -1;
    }
    char val = stack_arr[top];
    top--;
    return val;
}

void print_stack(){
    if(top == -1){
        printf("stack is empty...\n");
        return;
    }
    for(int i=top; i>=0; i--){
        printf("%d ",stack_arr[i]);
    }
    printf("\n");
}

int main(){
    
    char *str  = "(jfgdf(fjf{vfg}{jgd})";
    for(int i=0 ; i<strlen(str); i++){
        if(str[i] == '{' ||str[i] == '[' || str[i] == '{'){
            if(isfull()) {
                printf("loi!\n");
                return 1;
            }
            push(str[i]);
        }
        if(str[i] == '}' ||str[i] == ']' || str[i] == ')'){
            if(isempty){
                printf("not balance\n");
                return 0;
            }
            char  t = pop();
            if(t == '(' && str[i] == ')') continue;
            if(t == '{' && str[i] == ')') continue;
            if(t == '(' && str[i] == ')') continue;
            
            printf("loi!\n");
            return 1;


        }
        
    }
    if(isempty) printf("balance\n");
    return 0;
}