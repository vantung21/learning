#include<stdio.h>

int cnt = 0;
void out(int a[], int n){
    printf("%d:\t",++cnt);
    for(int i = 1; i<=n; i++){
        printf("%d",a[i]);
    }
    printf("\n");
}

void Try(int a[], int n,int i){
    for(int j = 0; j<=1; j++){
        a[i] = j;
        if(i == n) out(a,n);
        else{
            Try(a,n,i+1);
        }
    }
}

int main(){
    int a[101], n;
    scanf("%d",&n);
    Try(a,n,1);
}

