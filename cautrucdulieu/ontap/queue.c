#include <stdio.h>
#include <stdlib.h>

struct element{
    int ID;
    char* name;
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
    Q->capacity = capacity;
    Q->front = 0;
    Q->rear = -1;
    Q->count = 0;
    Q->queueArr = (struct element*)malloc(sizeof(struct element)*capacity);
    if(Q->queueArr == NULL) return NULL;
    return Q;
}

int isEmpty(Queue Q){
    return Q->count == 0;
}
int isFull(Queue Q){
    return Q->count == Q->capacity;
}

int increase(Queue Q, int value){
    value++;
    if(value == Q->capacity) value = 0;
    return value;
}

void enqueue(Queue Q, struct element e){
    if(isFull(Q)){
        printf("the queue is full!\n");
        return;
    }
    Q->rear = increase(Q, Q->rear);
    Q->queueArr[Q->rear] = e;
    Q->count++;
}

struct element* dequeue(Queue Q){
    if(isEmpty(Q)){
        printf("the queue is empty!\n");
        return NULL;
    }
    struct element* e = &Q->queueArr[Q->front];
    Q->front = increase(Q, Q->front);
    Q->count--;
    return e;
}

int main(){
    struct element e1, e2, e3, e4, e5, e6, e7, e8;
    e1.ID = 1; e1.name = "NVA";
    e2.ID = 2; e2.name = "NVB";
    e3.ID =3; e3.name = "NVC";
    e4.ID = 4; e4.name = "TVT";
    e5.ID = 5; e5.name = "LVT";
    e6.ID = 6; e6.name = "BMD";
    e7.ID = 7; e7.name = "NBN";
    e8.ID = 8; e8.name = "TTTT";

    Queue Q = create(5);
    enqueue(Q, e1);
    enqueue(Q, e2);
    enqueue(Q, e3);
    enqueue(Q, e4);
    struct element tmp = *dequeue(Q);
    printf("ID: %d\tname: %s\n",tmp.ID, tmp.name);
    tmp = *dequeue(Q);
    printf("ID: %d\tname: %s\n",tmp.ID, tmp.name);
    tmp = *dequeue(Q);
    printf("ID: %d\tname: %s\n",tmp.ID, tmp.name);
    enqueue(Q, e1);
    enqueue(Q, e5);
    enqueue(Q, e6);
    enqueue(Q, e7);
    enqueue(Q, e8);
    while(!isEmpty(Q)){
        tmp = *dequeue(Q);
        printf("ID: %d\tname: %s\n",tmp.ID, tmp.name);
    }

}