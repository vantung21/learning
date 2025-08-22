#ifndef point_h
#define point_h

#include <iostream>
using namespace std;

class point {
    private:
        int x,y;
    public:
        point (int x = 0, int y = 0): x(x), y(y) {};
        point (const point &p);
        void setpoint(int, int);
        void display();
};


#endif