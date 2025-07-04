#include <stdio.h>
#include <stdlib.h>

struct element{
    int value;
};
struct queueInfo{
    int capacity;
    int count;
    int rear;
    int front;
    struct element *queueArr;
};
typedef struct queueInfo *Queue;

Queue create(int capacity){
    Queue Q = (Queue)malloc(sizeof(struct queueInfo));
    if(Q == NULL) return NULL;
    Q->queueArr = (struct element*)malloc(sizeof(struct element)*capacity);
    if(Q->queueArr == NULL) return NULL;
    Q->capacity = capacity;
    Q->front = 0; 
    Q->rear = -1;
    Q->count = 0;
    return Q;
}

int isEmpty(Queue Q){
    return Q->count == 0;
}
int isFull(Queue Q){
    return Q->count == Q->capacity;
}

int increase(int value, Queue Q){
    if(++value == Q->capacity){
        value = 0;
    }
    return value;
}

void enqueue(Queue Q, struct element e){
    if(isFull(Q)){
        printf("the queue is full already! \n");
        return;
    }
    Q->rear = increase(Q->rear, Q);
    Q->queueArr[Q->rear] = e;
    Q->count++;
}
struct element* dequeue(Queue Q){
    if(isEmpty(Q)){
        printf("the queue is empty!\n");
        return NULL;
    }
    struct element *temp = &Q->queueArr[Q->front];
    Q->front = increase(Q->front, Q);
    Q->count--;
    return temp;
}
int main(){
    struct element e1, e2, e3, e4, e5, e6, e7, e8;
    e1.value = 2;
    e2.value = 4;
    e3.value = 1;
    e4.value = 3;
    e5.value = 10;
    e6.value = 13;
    e7.value = 8;
    e8.value = 7;

    Queue Q = create(5);

    enqueue(Q, e1);
    enqueue(Q, e2);
    enqueue(Q, e3);
    enqueue(Q, e4);
    printf("value: %d\n", (*dequeue(Q)).value);
    printf("value: %d\n", (*dequeue(Q)).value);
    printf("value: %d\n", (*dequeue(Q)).value);
    enqueue(Q, e5);
    enqueue(Q, e6);
    enqueue(Q, e7);
    enqueue(Q, e8);
    

    while(!isEmpty(Q)){
        //struct element t = dequeue(Q);
        printf("value: %d\n", (*dequeue(Q)).value);
    }
    return 0;
}