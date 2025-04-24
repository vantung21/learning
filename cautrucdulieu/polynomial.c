#include<stdio.h>
#include<stdlib.h>

#define MAX_SIZE 100

typedef struct PolyInfo{
    unsigned int high_power;
    int coeff[MAX_SIZE+1];
}*Polynomial;

Polynomial create(){
    Polynomial poly = (Polynomial)malloc(sizeof(struct PolyInfo));
    poly->high_power = 0;
    for(int i=0; i<= MAX_SIZE; i++){
        poly->coeff[i] = 0;
    }
    return poly;
}

int max(int a, int b){
    return a>b?a:b;
}

Polynomial add(Polynomial a, Polynomial b){
    Polynomial c = create();
    c->high_power = max(a->high_power,b->high_power);
    for(int i=0; i<= c->high_power; i++){
        c->coeff[i] = a->coeff[i] + b->coeff[i];
    }
    return c;
}

void show(Polynomial poly){
    for(int i = poly->high_power; i>=0; i--){
        printf("%dx^%u ",poly->coeff[i],i);
    }
    printf("\n");
}

Polynomial mult(Polynomial a, Polynomial b){
    Polynomial c = create();
    c->high_power = a->high_power + b->high_power;
    for(unsigned int i = 0; i<= a->high_power; i++){
        for(unsigned int j = 0; j<= b->high_power; j++){
            c->coeff[i+j] += a->coeff[i]*b->coeff[j];
        }
    }
    return c;
}

int main(){
    Polynomial a,b;
    a = create();
    b = create();
    
    int coeff_a[] = {1, -3, 2, 0, 0, 1};
    int coeff_b[] =             {-4,0,3};

    a->high_power = sizeof(coeff_a)/sizeof(coeff_a[0])-1;
    b->high_power = sizeof(coeff_b)/sizeof(coeff_b[0])-1;

    for(int i=0; i<= a->high_power; i++){
        a->coeff[i] = coeff_a[i];
    }
    for(int i=0; i<= b->high_power; i++){
        b->coeff[i] = coeff_b[i];
    }

    Polynomial c = add(a,b);
    show(c);

    c = mult(a,b);
    show(c);
    return 0;
}

