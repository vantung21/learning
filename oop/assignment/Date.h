#ifndef DATE_H
#define DATE_H

#include<iostream>
using namespace std;
class Date{
    private:
        int d,m,y;
        bool namNhuan(int y) const;
        int dayInMonth(int m, int y) const;
        void chuanHoa();
    public:
        Date(int =1, int =1, int = 1);
        Date(const Date &x);
        friend istream& operator >> (istream& in, Date &x);
        friend ostream& operator << (ostream& out, const Date &x);
        Date& operator ++ ();
        Date& operator -- ();
        Date operator ++ (int);
        Date operator -- (int);
        Date operator + (int) const;
        Date operator - (int) const;

};


#endif