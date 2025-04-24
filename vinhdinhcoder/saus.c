#include<stdio.h>
#include<string.h>
int main(){
    long tong = 0, pt[100]={0}, d=0;
   char s[1000];
   fgets(s,sizeof(s),stdin);
//    for(int i=0; i<strlen(s); i++){
//     printf("%c",s[i]);
//   }
   int index = strlen(s)-1;
   if (s[index] == '\n') {
        s[index] = '\0';
        index--;
   }
   for(int i=strlen(s)-1; i>=0; i--){
        if(s[i]=='+' || s[i]=='-' || i==0){
            d++;
            if(i==0 && s[i]!='-' && s[i]!='+'){
                for(int j =0 ; j<=index; j++ ){
                    pt[d] = pt[d]*10 + s[j]-48;
                }
                tong+=pt[d]; break;
            }
            for(int j =i+1 ; j<=index; j++ ){
                pt[d] = pt[d]*10 + s[j]-48;
            }
            index=i-1;
            
            if(s[i]=='+'){
                tong +=pt[d];
            }
            if(s[i]=='-') tong -= pt[d];
        }
   } 
   printf("%ld",tong);
}
