#include <stdio.h>
#include <string.h>
int main(){
    char s1[500];
    char s2[500];
    char doi;
    printf("Nhap tu thu nhat: ");
    scanf("%s",&s1);
    printf("Nhap tu thu hai: ");
    scanf("%s",&s2);
    int n1=strlen(s1);
    int n2=strlen(s2);
    if (n1!=n2){
        printf("Hai tu khong phai la anagram.");
        return 0;
    }
    for (int i=0;i<n1-1;i++){
        for (int j=i+1;j<n1;j++){
            if (s1[i]>s1[j]){
                doi=s1[i];
                s1[i]=s1[j];
                s1[j]=doi;
            }
        }
    }
     for (int i=0;i<n2-1;i++){
        for (int j=i+1;j<n2;j++){
            if (s2[i]>s2[j]){
                doi=s2[i];
                s2[i]=s2[j];
                s2[j]=doi;
            }
        }
    }
    for (int i=0;i<n1;i++){
        if (s1[i]!=s2[i]){
            printf("Hai tu khong phai la anagram.");
            return 0;
        }
     }
    printf("Hai tu la anagram.");
    return 0;
}
