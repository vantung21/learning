#include<stdio.h>
int main(){
    long long n,i=0;
    int a[10000], b[10000];
    scanf("%lld",&n);
    while(n>0){
        a[i]=n%2;
        i++;
        n/=2;
    }
    i--;
    for(int j=i;j>=0;j--){
        printf("%d",a[j]);
    }
        

}