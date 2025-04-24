#include<stdio.h>
void inkq(int n, int a[]){
    for(int i=1; i<=n; i++){
        printf("%d",a[i]);
    }
    printf("\n");
}
void sinhnhiphan(int i, int a[], int n){
    for(int j=0; j<=1; j++){
        a[i]=j;
        if(i==n){
            inkq(n,a);
        }
        else{
            sinhnhiphan(i+1,a,n);
        }
    }
}
int main(){
    int n, a[100];
    scanf("%d",&n);
    sinhnhiphan(1,a,n);
}