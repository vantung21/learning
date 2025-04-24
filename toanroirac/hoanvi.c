#include<stdio.h>
int n,a[100], final;
void swap(int *a, int *b){
    int c=*a; *a= *b; *b=c;
}
void ktao(){
    for(int i=1; i<=n; i++){
        a[i]=i;
    }
}
void sinh(){
    int i=n-1;
    while(i>=1 && a[i]> a[i+1]){
        i--;
    }
    if(i==0){
        final =0;
    }
    else {
        int j=n;
        while(a[i]>a[j]) j--;
        swap(&a[i], &a[j]);
        int l=i+1, r=n;
        while(l<r){
            swap(&a[l], &a[r]);
            l++; 
            r--;
        }
    }
}
int main(){
    scanf("%d",&n);
    final=1;
    ktao();
    while(final){
        for(int i=1; i<=n; i++){
            printf("%d",a[i]);
        }
        printf("\n");
        sinh();
    }
}