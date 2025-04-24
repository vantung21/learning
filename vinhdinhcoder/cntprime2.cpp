#include<stdio.h>
#include<math.h>

using namespace std;
long max(long a, long b){
    if(a>b) return a;
    return b;
}
int sang(long l, long r){
    int prime[r-l+1];
    int cnt=0;
    for(long i=0; i<r-l+1;i++){
        prime[i]=1;
    }
    for(int i=2; i<=sqrt(r); i++){
        for(int j=max(i*i,(l+i-1)/i*i); j<=r; j+=i){
            prime[j-l]=0;
        }
    }
    for(long i=max(l,2L);i<=r; i++){
        if(prime[i-l]) cnt++;
    }
    return cnt;
}
int main(){
    freopen("cntprime2.inp","r",stdin);
    freopen("cntprime2.out","w",stdout);
    long a,b;
    scanf("%ld%ld",&a,&b);

    printf("%d",sang(a,b));
    return 0;
}