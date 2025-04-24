#include<stdio.h>

#define ll long long
ll cnt = 0;
void out(int a[], int n){
    printf("%lld:\t",++cnt);
    for(int i = 1; i<=n; i++){
        printf("%d ",a[i]);
    }
    printf("\n");
}

void Try(int a[], int n, int k, int i){
    for(int j = 0; j<=k; j++){
        a[i] = j;
        if(i == n-1){
            a[n] = k-a[i];
            out(a,n);
        }
        else{
            Try(a,n,k-a[i],i+1);
        }
    }
}

int main(){
    int a[101], n, k;
    scanf("%d%d",&n,&k);
    Try(a,n,k,1);
}

