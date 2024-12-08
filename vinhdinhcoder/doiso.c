#include<stdio.h>
#include<math.h>
int main(){
    long long i=0,n,a,tong=0,kq=0,m[10];
    scanf("%lld",&n);
    a=n;
    while(a!=0){
        m[i]=a%10;
        i++;
        a/=10;
    }
    i--;
    for(int j=i;j>=0;j--){
        tong+=m[j];
    }
   if(tong%3==0){
    for(int j=0; j<i; j++){
        if(m[j]%3==0){
            kq+=3;
        }
        else { kq+=2; }
    }
    kq+=2;
   }
   else if(tong%3==1){
         for(int j=0; j<i; j++){
        if(m[j]%3==1){
            kq+=4;
        }
        else { kq+=3; }
    }
    kq+=3;
   }
   else if(tong%3==2){
    for(int j=0; j<i; j++){
        if(m[j]%3==2){
            kq+=4;
        }
        else { kq+=3; }
    }
    kq+=3;
   }
   printf("%lld",kq);

   
}