#include<stdio.h>

int cnt = 1;

void init(int a[], int n){
    for(int i=1; i<=n; i++){
        a[i] = 0;
    }
}

void printbinary(int a[], int n){
    printf("%d:\t",cnt++);
    for(int i=1; i<=n; i++){
        printf("%d",a[i]);
    }
    printf("\n");
}

void Sinh(int a[], int n, int* stop){
    int i = n;
    while(i>=1 && a[i]==1){
        a[i] = 0;
        i--;
    }
    if(i==0){
        *stop = 0;
    }
    else{
        a[i] = 1;
    }
}

int main(){
    int a[101], n, stop = 1;
    scanf("%d",&n);
    init(a,n);
    while(stop){
        printbinary(a,n);
        Sinh(a,n,&stop);
    }

    return 0;
}