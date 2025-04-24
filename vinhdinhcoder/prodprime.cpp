#include<iostream>
using namespace std;
int ckprime(int n){
    if(n==2) return 1;
    if(n==0||n==1||n%2==0) return 0;
    for(long i=3; i*i<=n;i+=2){
        if(n%i==0) return 0;
    }
    return 1;
}
int main(){
    freopen("prodprime.inp","r",stdin);
    freopen("prodprime.out","w",stdout);
    int n;
    cin>>n;
    if(ckprime(n+1)) cout <<"NO";
    else cout << "YES";
    return 0;

}