#include<stdio.h>
#include<string.h>
int main(){
    char s[1000];
    fgets(s,sizeof(s),stdin);
    int d=0;
    for(int i=0; i<strlen(s)-1;i++){
        if(s[i]==' ') d++;
    }
    printf("%d",d);
}