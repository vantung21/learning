#include<stdio.h>
#include<string.h>
int main(){
    char s1[1001],s2[1001];
    fgets(s1,sizeof(s1),stdin);
    fgets(s2,sizeof(s2),stdin);
    int d =0;
    d = strlen(s1)-strlen(s2);
    if(d<0) d=-d;
    printf("%d",d);

}