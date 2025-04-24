#include<stdio.h>

int n, cnt = 1;

void out( int a[], int k){
    printf("%d\t",cnt);
    for(int i=1; i<=k; i++){
        printf("%d",a[i]);
    }
    printf("\n");
    cnt++;
}
void Try(int i, int a[], int k){
    for(int j=a[i-1]+1; j<=n-k+i; j++){
        a[i]=j;
        if(i==k){
            out(a,k);
        }
        else{
            Try(i+1, a, k);
        }
    }
}
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    scanf("%d",&n);
    int k=n;
    int a[100];
    a[0]=0;
    while(k){
        Try(1,a,k);
        k--;
    }
   
}