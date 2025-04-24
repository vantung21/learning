#include<stdio.h>

int a[1000], b[1000], c[1000];

int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=0; i<n; i++){
        scanf("%d",&a[i]);
    }
    for(int i=0; i<m; i++){
        scanf("%d",&b[i]);
    }
    int cnt=0, i=0, j=0;
    while(i<n && j<m){
        if(a[i]<b[j]){
            c[cnt]=a[i];
            i++;
            cnt++;
        }
        else{
            c[cnt]=b[j];
            j++;
            cnt++;
        }
    }
    while(i<n){
        c[cnt]=a[i];
        cnt++; i++;
    }
    while(j<m){
        c[cnt]=b[j];
        cnt++; j++;
    } 
    for(int k=0; k<cnt; k++){
        printf("%d ",c[k]);
    }



}