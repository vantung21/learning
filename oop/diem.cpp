#include "diem.h"

void diem :: xuat(){
    cout << x << ", " << y << endl;
}

void diem :: dichuyen(double dx, double dy){
    x += dx; 
    y += dy;
}

double diem :: khoangcach(diem u){
    return sqrt(pow(this->x - u.x, 2) + pow(this->y - u.y, 2));
}

double khoangcach(diem a, diem  b){
    return sqrt(pow(a.x -b.x, 2) + pow(a.y - b.y, 2));
}