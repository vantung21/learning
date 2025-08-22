#include "point.h"

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