#include<iostream>
#include<math.h>
#include<algorithm>
using namespace std;
#define pi 3.14
int main(){
   int x,y;
   cin>> x>> y;
   int d=y/7;
   int q=y%7;
   int n=d*5;
   if(q==0){
      cout<< n;
      return 0;
   }
   
   for(int i=0; i<q; i++){
      if((x+i)%7 != 0 && (x+i)%8 != 0){
         n++;
      }
   }
   cout<<n;

   return 0;
  
}