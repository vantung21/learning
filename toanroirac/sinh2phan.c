#include<stdio.h>
void init(int b[], int n){
    for(int i=0; i<=n; i++){
        b[i]=0;
    }
}
void out(int b[], int n){
    for(int i=1; i<=n; i++){
        printf("%d",b[i]);
    }
    printf("\n");
}
int islast(int b[], int n){
    for(int i=1; i<=n; i++){
        if(b[i]==0) return 0;
    
    }
    return 1;
}
void gen(int b[], int n){
    int i=n;
    while(b[i]==1){
        b[i]=0;
        i--;
        
    } 
    b[i]=1;
    
}
int main(){
  
    int n; 
    scanf("%d",&n);
    int b[n+1];
    init(b,n);
    out(b,n);
    int stop=islast(b,n);
    while(stop==0){
        gen(b,n);
        out(b,n);
        stop=islast(b,n);
    }
}