#include<stdio.h>
#include<stdlib.h>
int cmp(const void *a,const void *b){
    return(*(long*)a-*(long*)b);
}
void sapxep(int a[], int n){
    qsort(a,n,sizeof(int),cmp);
}
int main(){
    int n,A[100000];
    scanf("%d",&n);
    for(int i=0 ; i<n; i++){
        scanf("%d",&A[i]);
    }
    sapxep(A,n);
    for(int i=0 ; i<n; i++){
        printf("%d ",A[i]);
    }
}