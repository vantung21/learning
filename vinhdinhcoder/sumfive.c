#include<stdio.h>
void swap(int *a,int *b){
    int tam = *a; *a=*b; *b=tam;
}
int tach(int a[], int low,int high ){
    int chot = a[high];
    int i=low-1;
    for(int j=low; j<=high; j++){
        // sap xep lon den be
        if(a[j]>chot){
            i++;
            swap(&a[i],&a[j]);
        }
    }
    swap(&a[i+1],&a[high]);
    return i+1;
}
// quicksort de quy
void quicksort(int a[],int low, int high){
    if(low<high){
        int q=tach(a,low,high);
        quicksort(a,low,q-1);
        quicksort(a,q+1,high);
    }
}
int main(){
    freopen("sumfive.inp","r",stdin);
    freopen("sumfive.out","w",stdout);
    int n,  b[5001];
    long long s=0;
    scanf("%d",&n);
    for(int i=0; i<n; i++){
        scanf("%d",&b[i]);
    }
    quicksort(b,0,n-1);
    for(int i=0; i<5; i++){
        s+=b[i];
    }
    printf("%lld",s);
}