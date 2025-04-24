#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

struct node{
    int coeff;
    int exp;
    struct node *next;
};

typedef struct node *polynomial;
typedef struct node *position;

polynomial create(){
    position header = (position)malloc(sizeof(struct node));
    header->exp = INT_MAX;
    header->next = NULL;
    return header;
}

void insert(polynomial poly, int coeff, int exp){
    position p = poly;
    while(p->next != NULL && p->next->exp >= exp){
        p = p->next;
    }

    if(p->exp == exp){
        p->coeff += coeff;
    }
    else{
        position newnode = (position)malloc(sizeof(struct node));
        newnode->coeff = coeff;
        newnode->exp = exp;
        newnode->next = p->next;
        p->next = newnode;
    }
}

polynomial add(polynomial a, polynomial b){
    polynomial c = create();
    a = a->next;
    b = b->next;
    while(a != NULL){
        insert(c,a->coeff,a->exp);
        a = a->next;
    }
    while(b != NULL){
        insert(c,b->coeff,b->exp);
        b = b->next;
    }
    return c;
}

polynomial mult(polynomial a, polynomial b){
    polynomial c = create();
    a = a->next;
    b = b->next;
    position temp;
    while(a != NULL){
        temp = b;
        while(b != NULL){
            insert(c, a->coeff *b->coeff, a->exp+b->exp);
            b = b->next;
        }
        b = temp;
        a = a->next;
    }
    return c;
}

void show(polynomial poly){
    poly = poly->next;

    while(poly != NULL){
        if(poly->coeff != 0){
            printf("%dx^%d ",poly->coeff, poly->exp);
        }
        poly = poly->next;
    }
    printf("\n");
}

int main(){
    polynomial a,b,c;
    a = create();
    b = create();

    insert(a,-1,5);
    insert(a,3,1);
    insert(a,1,0);

    insert(b,1,2);
    insert(b,-2,0);

    show(a);
    show(b);
    c = add(a,b);
    show(c);

    c = mult(a,b);
    show(c);

    return 0;
}