#include <iostream>
using namespace std;

void swap(int &a, int &b){
    int t = a; a =b; b = t;
}
int main(){
    int m = 5;
    int n = 10;
    void (*pswap)(int &, int &) = swap;
    (*pswap)(m,n);
    cout << m << " " << n << endl;

    return 0;
}