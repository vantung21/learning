#ifndef SET_H
#define SET_H
#include<iostream>
using namespace std;

class SET{
    private:
        int n, size;
        int *data;
    public:
        SET(int size = 100);
        SET(int arr[], int en, int size = 100);
        SET(const SET &s);
        ~SET(){
            delete [] data;
        }
        SET operator + (int a)const;
        SET operator - (int a) const ;
        SET operator + (const SET& s) const;
        SET operator - (const SET& s) const;
        SET operator * (const SET& s) const;
        bool operator()(int a) const;
        int& operator [](int idx);
        SET& operator = (const SET& s);
        friend ostream& operator << (ostream& out, const SET& s);
};


#endif