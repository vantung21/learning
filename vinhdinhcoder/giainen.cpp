#include<iostream>
#include<string.h>
using namespace std;
int main(){
    char s1[1000001], s2[1000001];
    fgets(s1,sizeof(s1), stdin );
    fgets(s2, sizeof(s2),stdin);
    char m=s1[0];
    int d=0;
    for(int i=0; i<strlen(s1)-1; i++){
        if(s1[i]==m){
            d++;
        }
        if(s1[i]!=m){
            printf("%d%c",d,m);
            d=1;
            m=s1[i];
        }
        if(i==strlen(s1)-2){
            printf("%d%c\n",d,m);
            d=0;
        }
    }
    for(int i=0 ; i<strlen(s1)-1; i++){
        if(s2[i]>='0'&&s2[i]<='9'){
            d=d*10 + s2[i]-48;
        }
        else {
            for(int j=0; j<d;j++){
                cout<<s2[i];
            }
            d=0;
        }
    }
}