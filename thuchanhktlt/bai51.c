#include<stdio.h>
#include <windows.h>

int chieurongmanhinh() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}
long long gt(int n);
long long tohop(int n, int k);
void tamgiacpascal(int n);
int dodai(int n);
int main(){
    int n;
    scanf("%d",&n);
    tamgiacpascal(n);
}
long long gt(int n){
    long long d=1,i;
    for( i=1; i<=n;i++){
        d*=i;
    }
    return d;
}
long long tohop(int n, int k){
    return gt(n)/(gt(k)*gt(n-k));
}
void tamgiacpascal(int n){
    int i,j;
    for( i=0;i<n;i++){
        for( j=1; j< (chieurongmanhinh()-dodai(i))/2; j++){
            printf(" ");
        }
        for( j=0; j<=i; j++){
            printf("%lld ", tohop(i, j));
        }
        printf("\n");
    }
}
int dodai(int n){
    int d=0,i;
    for( i=0; i<=n; i++){
        long long t= tohop(n,i);
        while(t){
            t/=10; d++;
        }
        d++;
    }
    return d;
}

