#ifndef diem_H
#define diem_H

#include <iostream>
#include <math.h>
using namespace std;

class diem{
    private:
        double x,y;
    public:
        diem(double x = 0, double y = 0): x(x), y(y) {};
        void xuat();
        void dichuyen(double dx, double dy);
        double khoangcach( diem u);
        friend double khoangcach(diem a, diem b);
};


#endif
