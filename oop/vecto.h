#ifndef VECTO_H
#define VECTO_H

#include<iostream>
using namespace std;

class vecto{
    private:
        int n; // so chieu
        double *data; // cac toa do
    public:
        vecto(int n = 2 );
        ~vecto();
        vecto(const vecto &v);
        void nhap();
        void xuat() const;
        friend istream &operator >> (istream &in , vecto &v);
        friend ostream &operator << (ostream &out, const vecto &v);
        vecto operator + (const vecto &v);
        const vecto operator = (const vecto &v) ;
        double &operator [] (int i) const;
};



#endif