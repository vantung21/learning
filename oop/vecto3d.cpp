#include <iostream>
using namespace std;

typedef struct vecto3d {
    double x;
    double y;
    double z;
}vecto3d;

vecto3d operator + (vecto3d A, vecto3d B){
    vecto3d C;
    C.x = A.x + B.x;
    C.y = A.y + B.y;
    C.z = A.z + B.z;
    return C;
}
vecto3d operator - (vecto3d A, vecto3d B){
    vecto3d C;
    C.x = A.x - B.x;
    C.y = A.y - B.y;
    C.z = A.z - B.z;
    return C;
}

double operator * (vecto3d A, vecto3d B){
    double s;
    s = A.x*B.x + A.y*B.y + A.z*B.z;
    return s;
}

istream& operator >> (istream& in ,vecto3d &A){
    in >> A.x >> A.y >> A.z;
    return in;
}
ostream& operator << (ostream& out, vecto3d A){
    out << "(" << A.x << "," << A.y << "," << A.z << ")" << endl;
    return out;
}

int main(){
    vecto3d A, B, C;
    cout << "Nhap vecto A: "; cin >>A;
    cout << "Nhap vecto B: "; cin >>B;
    cout << "A + B = "<< A+B ;
    cout << "A - B = " << A-B;
    cout << "A*B = " << A*B << endl;
    
    return 0;
}