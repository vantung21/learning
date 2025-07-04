#include <stdio.h>
#include <stdlib.h>

struct nodeInfo{
    int key;
    struct nodeInfo *p;
    struct nodeInfo *l;
    struct nodeInfo *r;
};

typedef struct nodeInfo* BST;
typedef struct nodeInfo* treenode;

void preorder(BST T){
    if(T != NULL){
        printf("%d ", T->key);
        preorder(T->l);
        preorder(T->r);
    }
}

void inorder(BST T){
    if(T != NULL){
        inorder(T->l);
        printf("%d ", T->key);
        inorder(T->r);
    }
}

treenode treeSearch(BST T, int key){
    if(T == NULL || T->key == key)
        return T;
    if(T->key > key)
        return treeSearch(T->l, key);
    else 
        return treeSearch(T->r, key);
}

treenode treeMinimum(BST T){
    while(T->l){
        T = T->l;
    }
    return T;
}

treenode treeMaximum(BST T){
    while(T->r){
        T = T->r;
    }
    return T;
}

treenode treeSuccessor(treenode x){
    if(x->r != NULL)
        return treeMinimum(x->r);
    treenode y = x->p;
    while(y != NULL && x == y->r){
        x = y;
        y = y->p;
    }
    return y;
}

void treeInsert(BST *T, int key){
    treenode z = (treenode)malloc(sizeof(struct nodeInfo));
    z->key = key;
    treenode y = NULL;
    treenode x = *T;
    while(x != NULL){
        y = x;
        if(key > x->key) x = x->r;
        else x = x->l;
    }
    z->p = y;
    z->l = NULL;
    z->r = NULL;
    if(y == NULL) *T  = z;
    else if(y->key > key) y->l = z;
    else y->r = z;
}

void treeDelete(BST *T, treenode z){
    treenode x,y;
    if(z->l == NULL || z->r == NULL) y = z;
    else y = treeSuccessor(z);
    if(y->l != NULL) x = y->l;
    else x = y->r;
    if(x != NULL) x->p = y->p;
    if(y->p == NULL) *T = x;
    else if(y->p->l == y) y->p->l = x;
    else y->p->r = x;
    if(y != z) z->key = y->key; 
}

int main(){
    BST T = NULL;
    treeInsert(&T, 10);
    treeInsert(&T, 2);
    treeInsert(&T, 15);
    preorder(T);
    printf("\n");
    inorder(T);
    printf("\n");
    treeDelete(&T, treeSearch(T, 10));
    preorder(T);
    printf("\n");
    inorder(T);
    printf("\n");

}