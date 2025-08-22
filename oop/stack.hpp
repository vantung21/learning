#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>

#define max 10
using namespace std;

class stack{
    private:
        int *Data;
        int maxsize;
        int top;
    public:
        stack(int maxsize = max);
        stack(const stack &s);
        ~stack();
        void push(int );
        int pop();
        bool isEmpty();
        bool isFull();
        void showstack();

};

stack :: stack (int maxsize){
    this->maxsize = maxsize;
    if(maxsize > 0){
        Data = new int[maxsize];
    }
    top = -1;
}

stack :: stack(const stack &s){
    maxsize = s.maxsize;
    Data = new int[maxsize];
    top = s.top;
    for(int i = 0 ; i <= s.top; i++){
        Data[i] = s.Data[i];
    }
}

stack :: ~stack(){
    cout << "thuc hien ham huy...\n";
    delete[] Data;
}

bool stack :: isEmpty(){
    return top ==-1;
}
bool stack :: isFull(){
    return top == maxsize -1;
}

void stack :: push(int x){
    if(!isFull()){
        top++;
        Data[top] = x;
    }
    else cout << "stack is full!\n";
}
int stack:: pop(){
    int t = Data[top];
    if(!isEmpty()){
        top--;
    }
    else cout << "stack is empty!\n";
    return t;
}

void stack :: showstack(){
    for(int i = top; i>=0; i--){
        cout << Data[i] << " ";
    }
    cout <<endl;
}

#endif