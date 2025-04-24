#include<stdio.h>
void swap(int *a, int *b){
    int c=*a; *a=*b; *b=c;
}
void init(int b[],int n){
    for(int i=1;i<=n; i++){
        b[i]=i;
    }
}
void out(int b[],int n){
    for(int i=1; i<=n ; i++){
        printf("%d",b[i]);
    }
    printf("\n");
}
void gen(int b[], int n,int *stop){
    int i=n-1;
    while(i>=1 && b[i]>b[i+1]){
        i--;
    }
    if(i==0){
        *stop=0;
    }
    else{
        int j=n; 
        while(b[j]<b[i]) j--;
        swap(&b[i],&b[j]);
        int l = i+1;
        int r= n;
        while(l<r){
            swap(&b[l],&b[r]);
            l++; r--;
        }
    }
}
int main (){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int b[100],n, stop=1;
    scanf("%d",&n);
    init(b,n);
    while(stop){
        out(b, n);
        gen(b,n, &stop);
    }
}