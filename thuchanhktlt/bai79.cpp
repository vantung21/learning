#include <stdio.h>
void nhap(long long n, long long matran[][500]){
    for(int i=0;i < n;i++){
        for (int j=0;j<n;j++){
            scanf("%lld",&matran[i][j]);
        }
    }
}
void xuat(long long n, long long matran[][500]){
    for(int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            printf("%lld ",matran[i][j]);
        }
        printf("\n");
    }
}
void trao_tong(long long n, long long matran[][500]){
    long long i=0,j=0,sum=0;
     long long max_index;
    for (i=0;i<n;i++){
        long long max=-1000000000;
        for(j=0;j<n;j++){
           
            if(max<matran[i][j]){
                 max=matran[i][j];
                 max_index=j;
                 }
        }
        if(max_index!=i){
            long long s=matran[i][i];
            matran[i][i]=matran[i][max_index];
            matran[i][max_index]=s;
        }
            sum+=max;  
          //  printf("%lld\n",sum);  
        }
    for (i=0;i<n;i++){
        for (j=0;j<n;j++){
            printf("%lld ",matran[i][j]);
        }
        printf("\n");
    }     
    printf("Tong cua cac phan tu lon nhat la: %lld",sum);     
     }
int main(){
    long long n;
    printf("Nhap kich thuoc ma tran: ");
    scanf("%lld",&n);
    long long a[n][500];
    nhap(n,a);
    printf("Ma tran A la: \n");
    xuat(n,a);
    printf("Ma tran moi la: \n");
    trao_tong(n,a);
    return 0;
}
