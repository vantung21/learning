#include "Linklist.h"

Linklist :: Linklist(): head(NULL), tail(NULL){}

Linklist :: ~Linklist(){
    while(head){
        Node* tmp = head;
        head = head->next;
        delete tmp;
    }
    tail = NULL;
}


Linklist :: Linklist(const Linklist &l){
    head = tail = NULL;
    Node* cur = l.head;
    while(cur){
        insert(cur->data);
        cur = cur->next;
    }
}

void Linklist :: addfirst(int x){
    Node* p = new Node(x);
    if(!head) head = tail = p;
    p->next = head;
    head = p;
}
void Linklist :: addlast(int x){
    Node* p = new Node(x);
    if(!head) head = tail = p;
    tail->next = p;
    tail = p;
}
void Linklist :: addafter(int y, int x){
    Node* cur = head;
    while(cur && cur->data != y) cur = cur->next;
    if(cur){
        Node* p = new Node(x);
        p->next = cur->next;
        cur->next = p;
        if(cur == tail) tail = p;
    }
}

void Linklist :: removefirst(){
    if(!head) return;
    Node* tmp = head;
    head = head->next;
    delete tmp;
    if(!head) tail = NULL;
}
void Linklist :: removelast(){
    if(!head) return;
    if(head == tail){ 
        delete head;
        head = tail = NULL;
    }
    Node* cur = head;
    while(cur->next != tail) cur = cur->next;
    delete tail;
    tail = cur;
    tail->next = NULL; 
}

void Linklist :: removeafter(int y){
    Node* cur = head;
    while(cur && cur->data !=y) cur = cur->next;
    if(cur && cur->next){
        Node* tmp = cur->next;
        cur->next = tmp->next;
        if(tmp == tail) tail = cur;
        delete tmp;
    }
}

void Linklist :: insert(int x){
    addlast(x);
}
void Linklist :: remove(int x){
    if(!head) return;
    if(head->data == x){
        removefirst();
        return;
    }

    Node* cur = head;
    while(cur->next && cur->next->data != x) cur = cur->next;
    if(cur->next){
        Node* tmp = cur->next;
        cur->next = tmp->next;
        if (tmp == tail) tail = cur;
        delete tmp;
    }
}

ostream& operator << (ostream& out, Linklist& l){
    Node* tmp = l.head;
    while(tmp){
        out << tmp->data << " "; 
        tmp = tmp->next;
    }
    return out;
}

void Linklist :: sort(bool (*cmp)(int, int)){
    for (Node* i = head; i && i->next; i = i->next) {
        for (Node* j = i->next; j; j = j->next) {
            if (cmp(j->data, i->data)){
                swap(i->data, j->data);
            }
        }
    }
}