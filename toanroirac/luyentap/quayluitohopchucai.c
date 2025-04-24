#include<stdio.h>
int cnt =0;
void out(char a[], int n){
    printf("%d:\t",++cnt);
    for(int i = 1; i<=n; i++){
        printf("%c",a[i]-1 + 'a');
    }
    printf("\n");
}

void Try(char a[], int n, int k, int i){
    for(int j = a[i-1] + 1; j<= n - k + i; j++){
        a[i] = j;
        if(i==k) out(a, k);
        else {
            Try(a,n,k,i+1);
        }
    }
}

int main(){
    char a[101]; int n=6;
    a[0] = 0;
    int k=n;
    while(k){
        Try(a,n,k,1);
        k--;
    }
    printf("%d:\t\n",++cnt); // tap con rong
    
}