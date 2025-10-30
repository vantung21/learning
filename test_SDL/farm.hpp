#ifndef FARM_HPP
#define FARM_HPP
#include "include.h"


class slot{
    private:
        int status;
        int slot_x, slot_y, slot_w, slot_h;
    public:
        slot(int x = 0, int y = 0, int w = 0, int h = 0): slot_x(x), slot_y(y), slot_w(w), slot_h(h) { status = 0; };
        void setSlot(int, int, int, int);
        void planted();
        void click();
};

void slot :: setSlot(int x, int y , int w, int h){
    slot_x = x;
    slot_y = y;
    slot_w = w;
    slot_h = h;
}

void slot :: planted(){
    status = 1;
}

void slot :: click(){
    if(status == 0) status = 1;
    if(status == 2) status = 0;
}

#endif