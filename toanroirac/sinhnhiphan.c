#include <stdio.h>
int n, a[100],k, final;
void ktao(){
    for (int i=1; i<=n; i++){
        a[i]=0;
    }
}
void sinh(){
    int i=n;
    while(i>=1 && a[i]==1){
        a[i]=0;
        i--;
    }
    if(i==0){
        final = 0;
    }
    else a[i]=1;
}
int check(){
    int cnt = 0;
    for(int i=1; i<=n; i++){
        cnt+=a[i];
    }
    return cnt == k;
}
int main(){
    scanf("%d%d",&n,&k);
    final = 1;
    ktao();
    while(final){
        if(check()){
            for(int i=1; i<=n; i++){
                printf("%d",a[i]);
            }
            printf("\n");
        }
       
        sinh();
    }
}