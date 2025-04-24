#include<stdio.h>

int cnt = 0;

void init(int a[], int k){
    for(int i=1; i<=k; i++){
        a[i] = i;
    }
}

void out(int a[], int k){
    printf("%d:\t",++cnt);
    for(int i=1; i<=k; i++){
        printf("%d",a[i]);
    }
    printf("\n");
}

void Sinh(int a[], int n, int k, int* stop){
    int i=k;
    while(i>=1 && a[i]==n-k+i) i--;
    if(i==0) *stop = 0;
    else{
        a[i]++;
        for(int j=i+1; j<=k; j++){
            a[j] = a[j-1]+1;
        }
    }
}

int main(){
    int a[101], n, stop = 1, k;
    scanf("%d%d",&n,&k);
    init(a,k);
    while(stop){
        out(a,k);
        Sinh(a,n,k,&stop);
    }
    return 0;
}