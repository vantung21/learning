#include <iostream>

using namespace std;

class Date{
    protected:
        int d,m,y;
        bool namNhuan(int y) const;
        int dayInMonth(int m, int y) const;
        void chuanHoa();
    public:
        Date(int =1, int =1, int = 1);
        Date(const Date &x);
        friend istream& operator >> (istream& in, Date &x);
        friend ostream& operator << (ostream& out, const Date &x);
        Date operator ++ ();
        Date operator -- ();
};

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

Date Date :: operator ++ (){
    d++; 
    chuanHoa();
    return *this;
}
Date Date :: operator -- (){
    d--;
    chuanHoa();
    return *this;
}

class Time{
    protected:
        int hour, minute, second;
    public:
        Time(int h= 0, int m = 0, int s = 0);
        Time operator ++ ();
        Time operator -- ();
        friend istream& operator >> (istream& in, Time &x);
        friend ostream& operator << (ostream& out, const Time &x);
            
};

Time :: Time(int h, int m, int s): hour(h), minute(m), second(s) {
    if(hour < 0 || hour > 23) hour = 0;
    if(minute < 0 || minute > 59) minute = 0;
    if(second <0 || second >59) second = 0;
}

Time Time :: operator ++ (){
    second++;
    if(second >= 60){
        second = 0;
        minute++;
        if(minute >= 60){
            hour++;
            minute = 0;
            if(hour >= 24){
                hour = 0;
            }
        }
    }
    return *this;
}

Time Time :: operator--(){
    second--;
    if(second < 0){
        second = 59;
        minute--;
        if(minute < 0){
            hour--;
            minute = 59;
            if(hour < 0){
                hour = 23;
            }
        }
    }
    return *this;
}

istream& operator >> (istream& in, Time &x){
    cout << "Nhap Time(hour minute second): ";
    in >> x.hour >> x.minute >> x.second;
    return in;
}

ostream& operator << (ostream& out, const Time &x){
    out << "time(hour/minute/second): " << x.hour << "/" << x.minute << "/" << x.second << endl;
    return out;
}

class DateTime
: public Date, Time{
    public:
        DateTime(int d = 1, int m = 1, int y = 1, int hour = 0, int minute = 0, int second = 0);
        DateTime operator ++();
        DateTime operator -- ();
        friend istream& operator >> (istream& in, DateTime &x);
        friend ostream& operator << (ostream&out, const DateTime &x);
};
DateTime::DateTime(int d, int m, int y, int hour, int minute, int second): Date(d,m,y), Time(hour, minute, second){}

DateTime DateTime::operator++(){
    Time::operator++();
    if(hour == 0 && minute == 0 && second == 0) Date::operator++();
    return *this;
}
DateTime DateTime::operator--(){
    Time::operator--();
    if(hour == 23 && minute == 59 && second == 59) Date::operator--();
    return *this;
}

istream& operator >> (istream& in, DateTime &x){
    cout << "Nhap DateTime (day month year hour minute second): ";
    in >> (Date&)(x) >> (Time&)(x);
    return in;
}
ostream& operator << (ostream&out, const DateTime &x){
    out << "DateTime:\n " << Date(x) << Time(x);
    return out;
}

int main(){
    Date d;
    cout << "Nhap ngay thang nam: ";
    cin >> d;
    cout << "Ban da nhap: " << d;

    cout << "Tang ngay: " << ++d;
    cout << "Giam ngay: " << --d;

    Time t;
    cin >> t;
    cout << t;

    cout << "Tang 1 giay: " << ++t;
    cout << "Giam 1 giay: " << --t;

    DateTime dt;
    cin >> dt;
    cout << dt;

    cout << "Tang 1 giay DateTime: " << ++dt;
    cout << "Giam 1 giay DateTime: " << --dt;

    return 0;
}