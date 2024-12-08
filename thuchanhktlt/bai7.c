#include<stdio.h>
#include<stdbool.h>
bool check(int B, int I, int T, int Y, int E);
int main(){
    int B,I,T,Y,E;
    for(int i=1; i<=9; i++){
        B=i;
        for(int j= 0; j<=9; j++){
            if(j==i) continue;
            I=j;
            for(int k=0; k<=9; k++){
                if(k==j||k==i) continue;
                T=k;
                for(int m=0; m<=9; m++){
                    if(m==i||m==j||m==k) continue;
                    Y=m;
                    for(int n=0; n<=9; n++){
                        if(n==m||n==k||n==j||n==i) continue;
                        E=n;
                        if(check(B,I,T,Y,E)){
                            int BIT=B*100+I*10+T;
                            int BYTE=B*1000+Y*100+T*10+E;
                            printf("%d*8 = %d\n",BIT,BYTE);
                        }
                    }
                }
            }
        }
    }
}
bool check(int B,int I,int T,int Y,int E){
    int BIT=B*100+I*10+T;
    int BYTE=B*1000+Y*100+T*10+E;
    return BIT*8==BYTE;
}