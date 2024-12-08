#include <stdio.h>
int main(){
    int n;
    scanf("%d",&n);
    for(int i=1; i<=n;i++){
        if(n%i==0&&i!=1){
            long m=0;
            for(int j=1; j<=(i/2); j++){
                if(i%j==0&&j!=1){
                    m++;
                }
            }
            if(m==0){
                printf("%d ",i);
            }
        }
    }
}