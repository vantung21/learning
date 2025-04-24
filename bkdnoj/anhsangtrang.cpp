#include<iostream>
#include<string.h>
using namespace std;
int min(int a, int b){
    if(a>b) return b; 
    return a;
}
int main(){
    int n, k;
    char s[200000];
    cin>> n>>k;
    cin>>s;
    int length = strlen(s);
    int index=0,a=0,q=0,I;
    char m[3]={'r','g','b'};
    while(index<length){
        I=index;
        for(int i=I; i<min(I+k, length);i++){
            if(s[i]==m[a]){
                index=i;
                a=(a+1)%3;
                break;
            }
            index++;
        }
        index++;
        q++;if(index==I+1) q--;
        if(m[a]!='b') q++;

    }
    cout <<q;
    return 0;
}