#include<iostream>
#include<cmath>
using namespace std;
int prime(long long a){
    for(int i=2;i<=sqrt(a); i++){
        if(a%i==0) return 0;
    }
     return a>1;
}
int main(){
    freopen("sum2prime.inp","r",stdin);
    freopen("sum2prime.out","w",stdout);
    long long n;
    cin>>n;
    for(long long i=2; i<=sqrt(n); i++){
        if(prime(i)&&prime(n-i)){
            cout<< i<<" "<<n-i;
            return 0;
        }
        if(i%2) i++;
    }
    cout<<-1;
    return 0;
}