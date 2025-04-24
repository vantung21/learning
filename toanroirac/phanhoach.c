#include<stdio.h>
int n,a[100], final, cnt;
void ktao(){
    cnt = 1;
    a[1]=n;
}
void sinh(){
    int i=cnt;
    while(i>=1 &&a[i]==1) i--;
    if(i==0){
        final=0;
    }
    else{
        a[i]--;
        int d=cnt-i+1;
        cnt = i;
        int q = d/a[i];
        int r = d%a[i];
        if(q){
            for(int j=1; j<=q; j++){
                cnt++;
                a[cnt]=a[i];
            }
        }
        if(r){
            cnt++;
            a[cnt]=r;
        }
    }
}
int main(){
    // freopen("input.txt","r",stdin);
    // freopen("output.txt","w",stdout);
    scanf("%d",&n);
    final=1;
    ktao();
    while(final){
        for(int i=1; i<=cnt; i++){
            printf("%d",a[i]);
        }
        printf("\n");
        sinh();
    }
}