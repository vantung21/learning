#include <stdio.h>

int x[100], a[100], b[100], c[100], n, cnt=1;
void Out();
void Try(int i);

int main(){
    scanf("%d", &n);
    for(int i = 0; i <= 2*n + 1; i++){
        a[i] = 1; b[i] = 1; c[i] = 1;
    }
    Try(1);
}

void Out(){
    printf("%d:\t",cnt++);
    for (int i = 1; i <= n; i++){
        printf("%d", x[i]);
    }
    printf("\n");
}

void Try(int i){
    for (int j = 1; j <= n; j++){
        if(a[j] == 1 && b[i+j] == 1 && c[i-j+(n-1)] == 1){
            x[i] = j;
            a[j] = 0; b[i+j] = 0; c[i-j+(n-1)] = 0;
            if(i == n){
                Out();
            }
            else{
                Try(i+1);
            }
            a[j] = 1; b[i+j] = 1; c[i-j+(n-1)] = 1;
        }
    }
}