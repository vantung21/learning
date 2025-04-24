#include<iostream>
#include<stdlib.h>
using namespace std;
int cmp(const void *a,const void *b){
    return(*(long*)a-*(long*)b);
}
void sapxep(int a[], int n){
    qsort(a,n,sizeof(int),cmp);
}
int prime[2000001];
void sieve(){
    prime[0]=prime[1]=0;
    for(int i=2; i<2000001; i++){
        prime[i]=1;
    }
    for(int i=2; i*i<=2000000; i++){
        if(prime[i]){
            for(int j=i*i; j<=2000000; j+=i){
                prime[j]=0;
            }
        }
    }
}
int main(){
    freopen("missingprime.inp","r",stdin);
    freopen("missingprime.out","w",stdout);
    sieve();
    int n, a[100000];
    cin>>n;
    for(int i=0; i<n; i++){
        cin>> a[i];
    }
    int i=2, m=0;
    sapxep(a,n);
    while(m<=n){
        if(prime[i]){
            if(a[m]<i){
                m++; continue;
            }
            if(a[m]==i){
                m++;i++; continue;
            }
            if(a[m]>i){
                cout<<i; return 0;
            }
        }
        i++;
    }
    cout <<"No prime number missing!"; 
    return 0;
}