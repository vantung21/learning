#include<iostream>
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
    if(l==1) prime[0]=0;
    for(int i=2; i<=sqrt(r); i++){
        for(long long j=max(i*i,(l+i-1)/i*i); j<=r; j+=i){
            prime[j-l]=0;
        }
    }
    for(long i=max(l,2L);i<=r; i++){
        if(prime[i-l]) cnt++;
    }
    return cnt;
}


int main(){
    freopen("cntprime3.inp","r",stdin);
    freopen("cntprime3.out","w",stdout);
    int k;
    cin>>k;
    int r,l;
    while(k--){
        cin >>l>>r;
        cout<<sang(l,r)<<endl;
        
    }
}