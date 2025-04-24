#include<stdio.h>
#include<string.h>
int main(){
    char s1[10001];
    scanf("%s",s1);
    int t=0;
    int check = 0;
    int index0 = -1, index5 = -1;
    for(int i=0; i<strlen(s1);i++){
        t+=s1[i]-48;
        if(s1[i]=='5' || s1[i]=='0'){
            check = 1;
            if(s1[i]=='0') index0 = i;
            if(s1[i]=='5') index5 = i;
        } 
    }
    if(index0!=-1){
        char a = s1[index0];
        s1[index0]=s1[0];
        s1[0]= a;
    }
    else {
         char a = s1[index5];
        s1[index5]=s1[0];
        s1[0]= a;
    }
   // printf("%d",check);

    if(t%9 == 0 && check==1){
        for(int i=1; i<strlen(s1)-1; i++){
            for(int j=i+1; j<strlen(s1);j++){
                if(s1[i]>s1[j]){
                    char m= s1[i];
                    s1[i]=s1[j];
                    s1[j]=m;
                }
            }
        }
        for(int i= strlen(s1)-1;i>=0;i--){
            printf("%c",s1[i]);
        }
    }
    else printf("-1");
}