#include <stdio.h>
#include <stdlib.h>

struct nodeInfo {
    struct nodeInfo *l;
    struct nodeInfo *r;
    struct nodeInfo *p;
    int key;
};

typedef struct nodeInfo *BST;
typedef struct nodeInfo *Treenode;

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
void postorder(BST T){
    if(T != NULL){
        postorder(T->l);
        postorder(T->r);
        printf("%d ", T->key);
    }
}

Treenode tree_search(BST T, int key){
    if(T == NULL || T->key == key)
        return T;
    if(T->key > key)
        return tree_search(T->l, key);
    else
        return tree_search(T->r, key);
}

Treenode treeMinimum(BST T){
    while(T->l != NULL){
        T = T->l;
    }
    return T;
}

Treenode treeMaximum(BST T){
    while(T->r != NULL){
        T = T->r;
    }
    return T;
}

Treenode treeSuccessor(Treenode x){
    if(x->r != NULL)
        return treeMinimum(x->r);
    Treenode y = x->p;
    while(y != NULL && x == y->r){
        x = y; 
        y = y->p;
    }
    return y;
}

void treeInsert(BST *T, int key){
    Treenode z = (Treenode)malloc(sizeof(struct nodeInfo));
    z->key = key;
    Treenode y = NULL;
    Treenode x = *T;
    while(x != NULL){
        y = x;
        if(x->key > z->key){
            x = x->l;
        }
        else{
            x = x->r;
        }
    }
    z->p = y;
    z->l = NULL;
    z->r = NULL;
    if(y == NULL)
        *T = z;
    else if(z->key < y->key)
        y->l = z;
    else    
        y->r = z;
}

Treenode treeDelete(BST *T, Treenode z){
    Treenode y, x;
    if(z->l == NULL || z->r == NULL){
        y = z;
    }
    else y = treeSuccessor(z);
    if(y->l != NULL) 
        x = y->l;
    else x = y->r;
    if(x != NULL)
        x->p = y->p;
    if(y->p == NULL)
        *T = x;
    else if(y == y->p->l)
        y->p->l = x;
    else y->p->r = x;
    if(y != z){
        z->key = y->key;
        // copy y's satellite data into z
    }
    return y;
}

int main(){
    BST T = NULL;
    treeInsert(&T, 10);
    treeInsert(&T, 5);
    treeInsert(&T, 30);
    treeInsert(&T, 2);
    treeInsert(&T, 25);
    treeInsert(&T, 45);
    treeInsert(&T, 20);
    preorder(T);
    printf("\n");
    inorder(T);
    printf("\n");
    postorder(T);
    Treenode a = tree_search(T, 24);
    if(a == NULL){
        printf("\ndeo co!!\n");
    }
    else
    printf("\n%d\n", a->key);

    a = treeMinimum(T);
    printf("\n%d\n", a->key);
    a = treeMaximum(T);
    printf("\n%d\n", a->key);

    treeDelete(&T, tree_search(T, 30));
    preorder(T);
    return 0;
}