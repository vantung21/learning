#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    long long data;
    struct node *next;
} node;

typedef node* nodeptr;

// tao node moi
nodeptr createnode(long long data){
    nodeptr newnode = (nodeptr)malloc(sizeof(node));
    newnode->data = data;
    newnode->next = NULL;
    return newnode;
}

//chen vao dau danh sach
void insertatbegin(nodeptr* head, long long data){
    nodeptr newnode = createnode(data);
    newnode->next = *head;
    *head = newnode;
}

//chen vao cuoi danh sach
void insertatend(nodeptr* head, long long data){
    nodeptr newnode = createnode(data);
    if(*head == NULL){
        *head = newnode;
        return;
    }
    nodeptr temp = *head;
    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = newnode;
}

// chen sau mot node cu the khi biet dia chỉ cua node do
void insertafter(nodeptr prevnode, long long data){
    if(prevnode == NULL){
        printf("node truoc khong ton tai!!!");
        return;
    }
    nodeptr newnode = createnode(data);
    newnode->next = prevnode->next;
    prevnode->next = newnode;
}

//chen vao vi tri cu the
void insertatposition(nodeptr* head, long long data, int position){
    nodeptr newnode = createnode(data);
    if(position == 0){
        newnode->next = *head;
        *head = newnode;
        return;
    }
    nodeptr temp = *head;
    for(int i=0; temp!=NULL && i<position-1; i++){
        temp = temp->next;
    }
    if(temp == NULL){
        printf("Vi tri vuot qua danh sach!!!"); return;
    }
    newnode->next = temp->next;
    temp->next = newnode;

}

//xoa ham theo gia tri
void delnode(nodeptr* head, long long key){
    nodeptr temp = *head, prev = NULL;
    if(temp!=NULL && temp->data == key){
        *head = temp->next;
        free(temp);
        return;
    }
    while(temp!=NULL && temp->data != key){
        prev = temp;
        temp = temp->next;
    }
    if(temp == NULL){
        return;
    }
    prev->next = temp->next;
    free(temp);
}

//ham in danh sach
void printlist(nodeptr head){
    while(head != NULL){
        printf("%lld  ",head->data);
        head = head->next;
    }
    printf("\n\n");
}

// ham dem so phan tu tron list
int sophantu(nodeptr head){
    int cnt = 0;
    while(head != NULL){
        cnt++;
        head= head->next;
    }
    return cnt;
}

//ham tao list
void nhap(nodeptr* head){
    long long a;
    int n;
    printf("so phan tu cua danh sach: ");
    scanf("%d",&n);
    for(int i=0; i<n; i++){
        printf("phan tu thu %d: ",i+1); scanf("%lld",&a);
        insertatend(head,a);
    }
}

// giai phong bo nho
void freelist(nodeptr* head) {
    nodeptr temp;
    while (*head != NULL) {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

int main(){
    nodeptr head = NULL;

    // insertatbegin(&head, 10);
    // insertatbegin(&head, 5);

    // insertatend(&head, 7);
    // insertatend(&head, 13);

    // printf("danh sach sau khi chen truoc va sau la: \n");
    // printlist(head);

    // insertafter(head->next->next, 29);
    // insertatposition(&head, 16,3);
    // printf("cac phan tu trong danh sach la:\n");
    // printlist(head);

    // printf("so luong phan tu: %d\n",sophantu(head));

    // delnode(&head, 5); delnode(&head, 13);
    // printf("danh sach sau khi xoa: \n");
    // printlist(head);
    // printf("so luong phan tu con lai la: %d\n",sophantu(head));
    nhap(&head);
    printlist(head);

    freelist(&head);
    return 0;
}