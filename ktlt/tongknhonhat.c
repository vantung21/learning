#include<stdio.h>
#include<stdlib.h>
int cmp(const void *a,const void *b){
    return(*(long*)a-*(long*)b);
}
void sapxep(long long a[], long n){
    qsort(a,n,sizeof(long long),cmp);
}
int main(){
    long n,k;
    scanf("%ld%ld",&n,&k);
    long long A[100001];
    for(int i=0; i<n; i++){
        scanf("%lld",&A[i]);
    }
    sapxep(A,n);
    // for(int i=0; i<n-1; i++){
    //     for(int j=i+1;j<n;j++){
    //         if(A[i]>A[j]){
    //             long long a=A[i];
    //             A[i]=A[j];
    //             A[j]=a;
    //         }
    //     }
    // }
    long long s=0;
    for(int i=0; i<k; i++){
        s+=A[i];
    }
    printf("%lld",s);
}