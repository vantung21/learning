#include<stdio.h>
void intohop(int k, int a[]){
    for(int i=1; i<=k; i++){
        printf("%d ",a[i]);
    }
    printf("\n");
}
void sinhtohop(int i, int n, int k, int a[]){
    for(int j=a[i-1]+1; j<=n-k+i; j++){
        a[i]=j;
        if(i==k){
            intohop(k,a);
        }
        else{
            sinhtohop(i+1,n,k,a);
        }
    }
}
int main(){
    int n, k,a[100];
    a[0]=0;
    scanf("%d%d",&n,&k);
    sinhtohop(1,n,k,a);
}