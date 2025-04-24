#include<stdio.h>
void out(int n, int a[]){
    for(int i=1; i<=n; i++){
        printf("%d",a[i]);
    }
    printf("\n");
}
void Try(int i, int n, int a[], int use[]){
    for(int j = 1; j<=n; j++){
        if(use[j]==0){
            a[i]=j;
            use[j]=1;
    
            if(i==n){
                out(n,a);
            }
            else{
                Try(i+1,n,a,use);
            }
            use[j]=0;
        }
        
    }
}
int main(){
    int use[100]={0}, n,a[100];
    scanf("%d",&n);
    Try(1,n,a,use);
    
}