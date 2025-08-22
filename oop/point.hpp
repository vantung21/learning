#ifndef point_hpp
#define point_hpp

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

void point :: setpoint(int xx, int yy){
    x = xx;
    y = yy;
}

void point :: display(){
    cout << "(" << x << " , " << y << ")" << endl;
}

point :: point(const point &p){
    this->x = p.x;
    this->y = p.y;
}


#endif