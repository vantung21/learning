#include<iostream>
using namespace std;
int prime[40001];
void sieve(){
    for(int i=2; i<=40000; i++){
        prime[i]=1;
    }
    prime[0]=prime[1]=0;
    for(int i=2; i<=200; i++){
        if(prime[i]){
            for(int j=i*i; j<=40000;j+=i){
                prime[j]=0;
            }
        }
    }
}
int main(){
    int n;
    cin>>n;
    // freopen("seqprime.inp","r",stdin);
    // freopen("seqprime.out","w",stdout);
    sieve();
    if(n%2){
        int i=2;
        while(n){
            if(prime[i]){
                cout<< i<<" ";
                n--;
            }
            i++;
        }
    }
    else{
        int i=3;
        while(n){
            if(prime[i]){
                cout<< i<<" ";
                n--;
            }
            i++;
        }
    }

}