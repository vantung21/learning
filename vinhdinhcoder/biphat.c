#include<stdio.h>
#include<math.h>
int main(){
    int n,m,s=0;
    scanf("%d",&n);
    for(int i=1; i<=n;i++){
        scanf("%d",&m);
        if(m==1){
            s++;
        }
        else if(m==2){
            s--;
        }
    }
    s=abs(s);
    printf("%d",s);
}