#include <stdio.h>
#include <stdlib.h>

struct node{
    struct node* p;
    struct node* l;
    struct node* r;
    int key;
};
typedef struct node *treenode;
typedef struct node *BST;

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
        printf("%d ",T->key);
        inorder(T->r);
    }
}
void postorder(BST T){
    if(T != NULL){
        postorder(T->l);
        postorder(T->r);
        printf("%d ",T->key);
    }
}

treenode tree_search(BST T, int key){
    if(T == NULL || T->key == key) return T;
    if(key < T->key) return tree_search(T->l, key);
    else return tree_search(T->r, key);
}

treenode treeMinimum(BST T){
    while(T->l != NULL){
        T= T->l;
    }
    return T;
}
treenode treeMaximum(BST T){
    while(T->r != NULL){
        T = T->r;
    }
    return T;
}

treenode treeSuccessor(treenode x){
    if(x->r != NULL) return treeMinimum(x->r);
    treenode y = x->p;
    while(y != NULL && x == y->r){
        x = y;
        y = y->p;
    }
    return y;
}

void treeInsert(BST *T, int key){
    treenode z = (treenode)malloc(sizeof(struct node));
    treenode y = NULL;
    treenode x = *T;
    z->key = key;
    while(x != NULL){
        y = x;
        if(key < x->key) x = x->l;
        else x = x->r;
    }
    z->p = y;
    z->l = NULL;
    z->r = NULL;
    if(y ==NULL) *T = z;
    else if(y->key > key) y->l = z;
    else y->r = z;
}

void treeDelete(BST *T, treenode z){
    treenode x, y;
    if(z->l == NULL || z->r == NULL) y = z;
    else y = treeSuccessor(z);
    if(y->l != NULL) x = y->l;
    else x = y->r;
    if(x != NULL) x->p = y->p;
    if(y->p == NULL) *T  = x;
    else if(y == y->p->l) y->p->l = x;
    else y->p->r = x;
    if(y != z){
        z->key = y->key;
    }
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
    treeDelete(&T, tree_search(T, 10));
    preorder(T);
    printf("\n");
    inorder(T);
    printf("\n");

}

