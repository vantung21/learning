#include<stdio.h>
#include<stdlib.h>
int cmp(const void *a, const void *b){
    return (*(long long*)b-*(long long*)a);
}
void sapxep(int a[], int n){
    qsort(a,n,sizeof(int),cmp);
}
int main(){
    freopen("bocbai.inp","r",stdin);
    freopen("bocbai.out","w",stdout);
    int n, a[1000001];
    scanf("%d",&n);
    for(int i=0; i<n; i++){
        scanf("%d",&a[i]);
    }
    sapxep(a,n);
    long long s1=a[0], s2=0;
    for(int i=1;i<n; i++){
        if(i%4==1|| i%4==2)
        s2+=a[i];
        if(i%4==0 || i%4==3)
        s1+=a[i];
    }
    if(s1>s2){
        printf("THANG");
    }
    if(s1==s2){
        printf("HOA");
    }
    if(s1<s2) printf("THUA");
}