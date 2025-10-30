#include "Date.h"

bool Date :: namNhuan(int y) const{
    return ((y%4==0 &&y%100 != 0) || y%400 == 0);
}
int Date :: dayInMonth(int m, int y) const {
    static int d[13] = {-1,31,28,31,30,31,30,31,31,30,31,30,31};
    if(m == 2) return namNhuan(y) ? 29 : 28;
    return d[m];
}
void Date :: chuanHoa(){
    while(d > dayInMonth(m,y)){
        d -= dayInMonth(m,y);
        m++;
        if(m >12){
            m = 1; y++;
        }
    }
    while(d <1){
        m--;
        if(m < 1){
            m = 12; y--;
        }
        d += dayInMonth(m, y);
    }
}

Date :: Date(int d, int m, int y): d(d), m(m), y(y) {
    chuanHoa();
}

Date :: Date(const Date &x){
    this->d = x.d;
    this->m = x.m;
    this->y = x.y;
}

istream& operator >> (istream& in, Date &x){
    in >> x.d >> x.m >> x.y;
    x.chuanHoa();
    return in;
}

ostream& operator << (ostream& out,const Date &x){
    out << x.d << "/"<< x.m << "/" << x.y <<endl;
    return out;
}

Date& Date :: operator ++ (){
    d++; 
    chuanHoa();
    return *this;
}
Date& Date :: operator -- (){
    d--;
    chuanHoa();
    return *this;
}
Date Date :: operator ++ (int){
    Date t = *this;
    ++(*this);
    return t;
}
Date Date :: operator -- (int){
    Date t = *this;
    --(*this);
    return t;
}

Date Date :: operator + (int a) const{
    Date t = *this;
    t.d +=a;
    t.chuanHoa();
    return t;
}
Date Date :: operator - (int a) const{
    Date t = *this;
    t.d -=a;
    t.chuanHoa();
    return t;
}