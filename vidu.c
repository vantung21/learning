// #include<stdio.h>

// int sum(int *a, int *b){
//     // *a -> 0x7ffd8aea0b0c
//     printf("Address of a %p \n", a);
//     printf("Address of b %p \n", b);
//     // *a => 2
//     return *a + *b;
// }

// int main(){
//    int n =2;
//    int m =4;
//         printf("Address of n %p \n", &n);
//     printf("Address of m %p \n", &m);
//     int s = sum(&n,&m);
//     // n=> 0x7ffd8aea0b0c
//     printf("Address of s %d \n", s);
// }

#include <stdio.h>

void swapnum(int &i, int &j) {
  int temp = i;
  i = j;
  j = temp;
}

int main(void) {
  int a = 10;
  int b = 20;

  swapnum(a, b);
  printf("A is %d and B is %d\n", a, b);
  return 0;
}