#include<stdio.h>
int cnt = 0;
void out(int a[], int n){
    printf("%d:\t",++cnt);
    for(int i = 1; i<=n; i++){
        printf("%d",a[i]);
    }
    printf("\n");
}
void Try(int a[], int n, int use[], int i){
    for(int j=1; j<=n; j++){
        if(use[j] == 0){
            a[i] = j;
            use[j] = 1;
            if(i==n) out(a,n);
            else{
                Try(a,n,use,i+1);
            }
            use[j]=0;
        }
    }
}

int main(){
    int a[101], n, use[101] = {0};
    scanf("%d",&n);
    Try(a,n,use,1);
}