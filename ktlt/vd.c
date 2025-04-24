#include<stdio.h>
void nhap(int A[], int n){
    for(int i=0; i<n; i++){
        scanf("%d",&A[i]);
    }
}
void xuat(int A[], int n){
    for(int i=0;i<n; i++){
        printf("%d ",A[i]);
    }
}


int main(){
    int n,A[100];
    printf("nhap n: ");
    scanf("%d",&n);
    nhap(A,n);
    xuat(A,n);

}