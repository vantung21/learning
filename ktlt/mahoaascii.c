#include<stdio.h>
#include<string.h>
int main(){
    char s[1001];
    scanf("%s",s);
    int i=0;
    while(i<strlen(s)){
        if(s[i]>'5'){
            int t=0;
            for(int j=i;i<i+2;j++){
                t=t*10 + s[j]-48;
            }
            printf("%c",t);
            i=i+2;
            if(i>=strlen(s)) return 0;
        }
        if(s[i]<5){
            int t=0;
            for(int j=i;i<i+3;j++){
                t=t*10 + s[j]-48;
            }
            printf("%c",t);
            i=i+3;
            if(i>=strlen(s)) return 0;
        }
    }
}