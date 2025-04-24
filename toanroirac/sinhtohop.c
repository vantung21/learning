#include<stdio.h>
int n,k,a[100],final;
void ktao(){
    for(int i=1; i<=k; i++){
        a[i]=i;
    }
}
void sinh(){
    int i=k;
    while(i>=1 && a[i]==n-k+i){
        i--;
    }
    if(i==0){
        final =0;
    }
    else {
        a[i]++;
        for(int j=i+1; j<=k; j++){
            a[j]= a[j-1]+1;
        }
    }
}
int main(){
    scanf("%d%d",&n,&k);
    final=1;
    ktao();
    while(final){
        for(int i=1; i<=k; i++){
            printf("%d",a[i]);
        }
        printf("\n");
        sinh();
    }
}