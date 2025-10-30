#include "Date.h"
#include<iostream>

using namespace std;

int main(){
    Date d1;
    cout << "Nhap ngay thang nam (d m y): ";
    cin >> d1;

    cout << "Ngay vua nhap: " << d1 << endl;

    cout << "ngay hom sau : " << ++d1 << endl;
    --d1;
    cout << "ngay truoc do : " << --d1 << endl;

    int k;
    cout << "Nhap so nguyen k: "; cin >> k;
    Date d2 = d1 +k;
    Date d3 = d1 -k;
    cout << "sau k ngay: " << d2 << endl;
    cout << "truoc k ngay:  " << d3 << endl;
    return 0;
}