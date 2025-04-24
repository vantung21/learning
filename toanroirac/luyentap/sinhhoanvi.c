#include<stdio.h>
int cnt = 0;

void swap(int* a, int* b){
    int t = *a; *a = *b; *b = t;
}

void init(int a[], int n){
    for(int i=1; i<=n; i++){
        a[i] = i;
    }
}

void out(int a[], int n){
    printf("%d:\t",++cnt);
    for(int i = 1; i<=n; i++){
        printf("%d",a[i]);
    }
    printf("\n");
}

void Sinh(int a[], int n, int *stop){
    int i = n-1;
    while(i>=1 && a[i]>a[i+1]) i--;
    if(i==0) *stop = 0;
    else{
        int j = n;
        while(a[j] < a[i]) j--;
        swap(&a[i],&a[j]);
        int l = i+1, r = n;
        while(l<r){
            swap(&a[l], &a[r]);
            l++; r--;
        }
    }     
}

int main(){
    int a[101], n, stop = 1;
    scanf("%d", &n);
    init(a,n);

    while(stop){
        out(a,n);
        Sinh(a,n,&stop);
    }
}