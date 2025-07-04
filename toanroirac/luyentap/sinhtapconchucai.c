#include<stdio.h>

int cnt = 0;

void init(char a[], int k){
    for(int i=1; i<=k; i++){
        a[i] = 'a' + i-1;
    }
}

void out(char a[], int k){
    printf("%d:\t",++cnt);
    for(int i=1; i<=k; i++){
        printf("%c",a[i]);
    }
    printf("\n");
}

void Sinh(char a[], int n, int k, int* stop){
    int i=k;
    while(i>=1 && a[i]==n-k+i +'a'-1) i--;
    if(i==0) *stop = 0;
    else{
        a[i]++;
        for(int j=i+1; j<=k; j++){
            a[j] = a[j-1]+1;
        }
    }
}

int main(){
    char a[101]; int n, stop;
    scanf("%d",&n);
    int k = n;
    while(k){
        stop = 1;
        init(a,k);
        while(stop){
            out(a,k);
            Sinh(a,n,k,&stop);
        }
        k--;
    }
    
    return 0;
}