#include "diem.h"

int main(){
    diem a(3,4);
    a.xuat();
    diem b(5,9);
    double kc = b.khoangcach(a);
    double m = khoangcach(a,b);
    cout << kc << " ," << m << endl;

    return 0;
}