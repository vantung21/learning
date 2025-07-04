#include <stdio.h>
int kq[100];
int cnt = 0;
int s;
void out(){
    cnt++;
    printf("%d:\t", cnt);
    for(int i = 1; i<=s ; i++){
        if(kq[i] == 0){
            printf("%c ",'X');
        }
        else if(kq[i] == 1){
            printf("%c ", 'D');
        }
        else printf("%c ", 'V');
    }
    printf("\n");
}

void xepbi(int i, int a[]){
    for(int j = 0; j<3; j++){
        if(a[j] > 0 && kq[i-1] != j){
            kq[i] = j;
            a[j]--;
            if(i == s){
                out();
            }
            else{
                xepbi(i+1, a);
            }
            a[j]++;
        }
        
    }
}

int main(){
    printf("nhap tong so bi: ");
    scanf("%d", &s);
    printf("nhap so bi tung loai (X, D, V):\n");
    int a[3];
    for(int i = 0; i<3; i++){
        scanf("%d", &a[i]);
    }
    kq[0] = -1;
    xepbi(1, a);

    return 0;
}