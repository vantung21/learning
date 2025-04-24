// // #include<stdio.h>

// // int n,m,stop = 1,a[100];

// // void out(){
// //     for(int i=1; i<=m; i++){
// //         printf("%d ",a[i]);
// //     }
// // }
// // void init(){
// //     a[1]=n;
// //     for(int i=2; i<=m; i++){
// //         a[i]=0;
// //     }
// // }

// // void sinh(){
// //     int i=m;
// //     while(i>1 && a[i-1]-a[i]<=1) i--;
// //     if(i==1){
// //         stop = 0;
// //     }
// //     else{
// //         int s=0;
// //         for(int j=i+1; j<=m; j++){
// //             s+=a[j];
// //         }
// //         a[i]--;
// //         a[i+1]=s+1;
// //         for(int j=i+2; j<=m;j++){
// //             a[j]=0;
// //         } 
// //     }
// // }


// // int main(){
// //     scanf("%d%d",&m,&n);
// //     init();
// //     while(stop){
// //         out();
// //         sinh();
// //     }
// // }

// #include <stdio.h>

// int n, m, stop = 1, a[100];

// void out() {
//     for (int i = 1; i <= m; i++) {
//         printf("%d ", a[i]);
//     }
//     printf("\n");
// }

// void init() {
//     a[1] = n;
//     for (int i = 2; i <= m; i++) {
//         a[i] = 0;
//     }
// }

// void sinh() {
//     int i = m;
    
//     // Tìm vị trí có thể giảm
//     while (i > 1 && a[i - 1] - a[i] <= 1) {
//         i--;
//     }
    
//     if (i == 1) {
//         stop = 0;  // Không thể sinh thêm
//     } else {
//         a[i - 1]--;  // Giảm phần tử a[i-1]

//         int sum = 0;
//         for (int j = i; j <= m; j++) {
//             sum += a[j];  // Tính tổng phần còn lại
//         }

//         a[i] = sum + 1;  // Đặt lại giá trị phần tử i
//         for (int j = i + 1; j <= m; j++) {
//             a[j] = 0;  // Đặt các phần tử sau thành 0
//         }
//     }
// }

// int main() {
//     scanf("%d%d", &n, &m);
    
//     // Kiểm tra điều kiện hợp lệ
//     if (m > n) {
//         printf("Khong co phan tich nao!\n");
//         return 0;
//     }

//     init();
//     while (stop) {
//         out();
//         sinh();
//     }
    
//     return 0;
// }

#include<stdio.h>
int main(){
    int n, cnt=1;
    scanf("%d",&n);
    for(int i=0; i<=n; i++){
        for(int j=0; j<=n; j++){
            for(int k=0; k<=n; k++){
                if(i+j+k==n)
                printf("%d\t%d %d %d\n",cnt++,i,j,k);

            }
        }
    }
}