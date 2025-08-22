#include "point.hpp"

int main(){
    point a, b;
    a.setpoint(2,4);
    b.setpoint(3,7);

    a.display();
    b.display();

    point c(1,2);
    point d;
    c.display();
    d.display();

    point e(c);
    e.display();

    return 0;
}