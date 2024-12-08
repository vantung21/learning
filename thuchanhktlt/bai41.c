// #include <stdio.h>
// int main(){
//     double n;
//     int dem=0;
//     for(int a=1; a<=9; a++){
//         for(int b=0; b<=9; b++){
//             if(b==a) continue;
//             for(int c=0;c<=9; c++){
//                 if(c==a||c==b) continue;
//                 for(int d=0; d<=9; d++){
//                     if(d==a||d==b||d==c) continue;
//                     n= a+b*0.1+c*0.01+d*0.001;
//                     dem++;
//                     printf("%.3lf  ",n);
//                 }
//                 printf("\n");
//             }
//         }
//     }
//     printf("co %d so thoa man",dem);
// }

#include<stdio.h>
void lietke(int A[4]);
int main(){
    int A[4];
    printf("nhap 4 chu so trong khoang 0->9: ");
    for(int i=0; i<4; i++){
        scanf("%1d",&A[i]);
    }
    lietke(A);
}
void lietke(int A[4]){
    int d=0;
    for(int i=0; i<4; i++){
        for(int j=0 ; j<4; j++){
            if(j==i) continue;
            for(int k=0; k<4; k++){
                if(k==j||k==i) continue;
                for(int l=0; l<4; l++){
                    if(l==k||l==j||l==i) continue;
                    if(A[l]==0) continue;
                    printf("%.3lf  ",A[i]+A[j]*0.1+A[k]*0.01+A[l]*0.001);
                    d++;
                }
            }
        }
        printf("\n");
    }
    printf("Co %d so thoa man",d);
}