#include "Polynomial.h"

int main(){
    Polynomial p1(5), p2(4);
    cout << " nhap p1: ";
    cin >> p1;
    cout << "nhap p2: ";
    cin >> p2;
    cout <<"p1: " << p1 <<"p2: " << p2;
    Polynomial p3 = p1 +p2;
    cout <<"p3: " << p3;
    Polynomial p4;
    p4 = p3  -p1;
    cout <<"p4: " << p4;
    cout << "he so thu 2 cua p4 la: " << p4[2] << endl;
    cout << "gia tri p3(7) = " << p3(7) << endl;


    return 0;
}