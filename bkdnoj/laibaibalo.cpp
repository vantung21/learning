#include<iostream>
#include<stdlib.h>
using namespace std;
int cmp(const void *a,const void *b){
    return(*(long*)a-*(long*)b);
}
void sapxep(int a[], int n){
    qsort(a,n,sizeof(int),cmp);
}
int main(){
    int n,m,a[100000];
    cin>> n>> m;
    for(int i=0; i<m; i++){
        cin>> a[i];
    }
    sapxep(a,m);
    int b[100000];
    b[0]=a[0];
    for(int i=1; i<m; i++){
        b[i]=b[i-1]+a[i];
    }
    for(int i=0; i<m;i++){
        if(b[i]>n){
            cout << i;
            return 0;
        }
    }
    cout << m;
    return 0;
}