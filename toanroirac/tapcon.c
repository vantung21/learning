#include<stdio.h>
void init(int k,int a[]){
    for(int i=1; i<=k; i++){
        a[i]=i;
    }
}
void out(int k, int a[]){
    for(int i=1; i<=k; i++){
        printf("%d ",a[i]);
    }
    printf("\n");
}
void sinh(int n, int a[],int k,int *stop){
    int i=k;
    while(i>=1&&a[i]==n-k+i){
        i--;
    }
    if(i==0){
        *stop=0;
    }
    else{
        a[i]+=1;
        for(int j=i+1; j<=k;j++){
            a[j]=a[j-1]+1;
        }
    }
}
int main(){
    int n,a[100],stop = 1,k;
    printf("nhap so luong phan tu: ");
    scanf("%d",&n);
    k=n;
    while(k){
        init(k,a);
        while(stop){
            out(k,a);
            sinh(n,a,k,&stop);
            
        }
        stop =1;
        k--;
    }
    
}