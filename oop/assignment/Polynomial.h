#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include<iostream>
#include<math.h>
using namespace std;

class Polynomial{
    private:
        int n;
        int* coeff;
    public:
        Polynomial(int n = 0);
        ~Polynomial();
        Polynomial(const Polynomial &p);
        Polynomial operator + (const Polynomial &p) const;
        Polynomial operator - (const Polynomial &p) const;
        friend istream& operator >> (istream& in, Polynomial &p);
        friend ostream& operator << (ostream& out, Polynomial &p);
        Polynomial& operator = (const Polynomial& p);
        int operator [] (int x) const;
        int operator () (int x);
};

#endif