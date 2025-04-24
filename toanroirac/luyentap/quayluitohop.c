#include<stdio.h>
int cnt =0;
void out(int a[], int n){
    printf("%d:\t",++cnt);
    for(int i = 1; i<=n; i++){
        printf("%d",a[i]);
    }
    printf("\n");
}

void Try(int a[], int n, int k, int i){
    for(int j = a[i-1] + 1; j<= n - k + i; j++){
        a[i] = j;
        if(i==k) out(a, k);
        else {
            Try(a,n,k,i+1);
        }
    }
}

int main(){
    int a[101], n, k;
    a[0] = 0;
    scanf("%d%d",&n,&k);
    Try(a,n,k,1);
}