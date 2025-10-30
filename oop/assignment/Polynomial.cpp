#include "Polynomial.h"

Polynomial :: Polynomial(int n): n(n){
    coeff = new int[n+1]();
}
Polynomial :: ~Polynomial(){ delete [] coeff;}

Polynomial :: Polynomial(const Polynomial &p){
    n = p.n;
    coeff = new int[n+1];
    for(int i = 0; i<=n; i++){
        coeff[i] = p.coeff[i];
    }
}

Polynomial Polynomial :: operator + (const Polynomial &p) const{
    int c = max(n, p.n);
    Polynomial t(c);
    for(int i=0; i<=c; i++){
        if(i <= n && i<= p.n) t.coeff[i] = coeff[i] + p.coeff[i];
        else if(i > n && i <=p.n) t.coeff[i] = p.coeff[i];
        else if(i <= n && i> p.n) t.coeff[i] = coeff[i];
    }
    return t;
}

Polynomial Polynomial :: operator - (const Polynomial &p) const{
    int c = max(n, p.n);
    Polynomial t(c);
    for(int i=0; i<=c; i++){
        if(i <= n && i<= p.n) t.coeff[i] = coeff[i] - p.coeff[i];
        else if(i > n && i <=p.n) t.coeff[i] = -p.coeff[i];
        else if(i <= n && i> p.n) t.coeff[i] = coeff[i];
    }
    return t;
}

istream& operator >> (istream& in, Polynomial &p){
    cout << "nhap cac he so cua da thuc P(" << p.n << ") :\n";
    for(int i = 0; i<=p.n; i++){
        cout << "nhap a" << i << ": "; 
        in >> p.coeff[i];
    }
    return in;
}
ostream& operator << (ostream& out, Polynomial &p){
    out << "da thuc p(" << p.n << ") : \n";
    for(int i =0; i<=p.n; i++){
        out << p.coeff[i] <<"*X^" << i << " ";
    }
    out << endl;
    return out;
}

Polynomial& Polynomial :: operator = (const Polynomial& p){
    if(this != &p){
        n = p.n;
        delete [] coeff;
        coeff = new int[n+1];
        for(int i =0; i<=n; i++){
            coeff[i] = p.coeff[i];
        }
    }
    return *this;
}

int Polynomial :: operator [] (int x)const{
    return coeff[x];
}

int Polynomial :: operator () (int x){
    int s = 0;
    for(int i =0; i<=n; i++){
        s+= pow(x,i)*coeff[i];
    }
    return s;
}