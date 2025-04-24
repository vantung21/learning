#include<stdio.h>
int cnt = 0, a[101], b[101], c[101], x[101];
void out( int n){
    printf("%d:\t",++cnt);
    for(int i = 1; i<=n; i++){
        printf("%d",x[i]);
    }
    printf("\n");
}

void Try(int n, int i){
    for(int j=1; j<=n; j++){
        if(a[j]&&b[i+j]&&c[i-j+n-1]){
            x[i] = j;
            a[j] = b[i+j] = c[i-j + (n-1)] = 0;
            if(i==n) out(n);
            else{
                Try(n,i+1);
            }
            a[j] = b[i+j] = c[i-j +n-1] = 1;
        }
    }
}

int main(){
    int n;
    scanf("%d",&n);
    for(int i=1; i<=2*n+1; i++){
        a[i] = b[i] = c[i] = 1;
    }
    Try(n,1);
}