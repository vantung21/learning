#include<stdio.h>

int a[10001];
int size = 0;

void swap(int i, int j){
    int t = a[i];
    a[i] = a[j]; a[j] = t;
}

int isEmpty(){
    return size <= 0;
}

int peek(){
    if(isEmpty()){
        printf("error: heap is empty...\n");
        return -1;
    }
    return a[1];
}

void heapifyUp(int i){
    int curIndex = i;
    int parentIndex = curIndex/2;

    while(parentIndex != 0 && a[parentIndex] >a[curIndex]){
        swap(curIndex, parentIndex);
        curIndex = parentIndex;
        parentIndex = curIndex/2;
    }
}

void add(int v){
    size++;
    a[size] = v;
    
    //heapify up
    heapifyUp(size);
}

void heapifyDown(int i){
    int curIndex = i;
    while(curIndex*2 <=size){
        int leftchildIndex = 2*curIndex;
        int rightchildIndex = 2*curIndex + 1;
        int smallerchildIndex = leftchildIndex;

        if(rightchildIndex<=size && a[rightchildIndex]<a[leftchildIndex]){
            smallerchildIndex = rightchildIndex;
        }

        if(a[smallerchildIndex] < a[curIndex]){
            swap(smallerchildIndex, curIndex);
            curIndex = smallerchildIndex;
        }
        else{
            break;
        }  
    }
}

//remove root
int poll(){
    if(isEmpty()){
        printf("error: heap is empty...\n");
        return -1;
    }
    int root = a[1];
    a[1] = a[size];
    size--;

    //heapify down
    heapifyDown(1);

    return root;
}

void remove(int v){
    int curIndex =-1;
    for(int i=1; i<=size; i++){
        if(a[i] == v){
            curIndex = i; break;
        }
    }
    if(curIndex == -1){
        printf("error: Element is not exist!!\n");
        return;
    }
    a[curIndex] = a[size];
    size--;
    if(a[curIndex] < a[curIndex/2]){
        heapifyUp(curIndex);
    }
    else heapifyDown(curIndex);
}

        
int main(){
    add(18);
    add(11);
    add(12);
    add(3);
    add(45);
    add(9);
    remove(11);
    remove(3);
    while(size){
        printf("%d\t",poll());
    }

}