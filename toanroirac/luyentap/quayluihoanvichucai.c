#include<stdio.h>
int cnt = 0;
void out(char a[], int k){
    printf("%d:\t",++cnt);
    for(int i = 1; i<=k; i++){
        printf("%c",a[i]-1 + 'a');
    }
    printf("\n");
}
void Try(char a[], int n, int k, int use[], int i){
    for(int j=1; j<=n; j++){
        if(use[j] == 0){
            a[i] = j;
            use[j] = 1;
            if(i==k) out(a,k);
            else{
                Try(a,n,k,use,i+1);
            }
            use[j]=0;
        }
    }
}

int main(){
    char a[101]; int n, k,  use[101] = {0};
    scanf("%d%d",&n,&k);
    Try(a,n,k,use,1);
}