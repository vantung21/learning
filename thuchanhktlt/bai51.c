#include<stdio.h>
long long gt(int n);
long long tohop(int n, int k);
void tamgiacpascal(int n);
int main(){
    int n;
    scanf("%d",&n);
    tamgiacpascal(n);
}
long long gt(int n){
    long long d=1;
    for(int i=1; i<=n;i++){
        d*=i;
    }
    return d;
}
long long tohop(int n, int k){
    return gt(n)/(gt(k)*gt(n-k));
}
void tamgiacpascal(int n){
    for(int i=0;i<n;i++){
        for(int j=1; j< n-i; j++){
            printf(" ");
        }
        for(int j=0; j<=i; j++){
            printf("%lld ", tohop(i, j));
        }
        printf("\n");
    }
}