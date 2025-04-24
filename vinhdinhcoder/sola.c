#include<stdio.h>
#include<stdlib.h>
int cpm(const void *a, const void *b){
    return *(int*)a- *(int*)b;
}
void sapxep(int a[], int n){
    qsort(a,n,sizeof(int), cpm);
}
int prime[1000001];
void sieve(){
    for(int i=2; i<=1000000; i++){
        prime[i]=1;
    }
    prime[0]=prime[1]=0;
    for(int i=2; i*i<=1000000; i++){
        if(prime[i]){
            for(int j=i*i; j<=1000000; j+=i){
                prime[j]=0;
            }
        }
    }
}
int main(){
    freopen("sola.inp","r",stdin);
    freopen("sola.out","w",stdout);
    sieve();
    int n,a[1000000];
    scanf("%d",&n);
    for(int i=0; i<n; i++) scanf("%d",&a[i]);
    sapxep(a,n);
    int cnt=0;
    for(int i=0; i<n; i++){
       // if(prime[a[i]]) continue;
        int d=1;
        if(a[i]==a[i+1]) continue;
        for(int j=0; j<i; j++){
            if(a[i]%a[j]==0){
                d=0; continue;
            }
        }
        if(d) cnt++;
    }
    printf("%d",cnt);
}
