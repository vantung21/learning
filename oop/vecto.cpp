#include "vecto.h"
vecto :: vecto(int n): n(n), data(new double[n]){};

vecto :: ~vecto(){
    delete [] data;
}

vecto :: vecto(const vecto &v): n(v.n){
    data = new double[n];
    for(int i = 0; i<n; i++){
        this->data[i] = v.data[i];
    }
}

void vecto :: nhap(){
    for(int i = 0; i<n; i++){
        cout << "nhap toa do thu " << i+1 <<": ";
        cin >> data[i];
    }
}

void vecto :: xuat() const {
    cout << "( ";
    for(int i =0; i<n; i++){
        cout << data[i] << ", ";
    }
    cout << ")"<< endl;
}

istream &operator >> (istream &in , vecto &v){
    for(int i = 0; i<v.n; i++){
        cout << "nhap toa do thu " << i+1 <<": ";
        in >> v.data[i];
    }
    return in;
}

ostream &operator << (ostream &out, const vecto &v){
    out << "( ";
    for(int i =0; i<v.n; i++){
        out << v.data[i] << ", ";
    }
    out << ")"<< endl;
    return out;
}

vecto vecto :: operator + (const vecto &v){
    if(n == v.n){
        vecto t(n);
        for(int i = 0; i<n; i++){
            t[i] = (*this)[i] + v.data[i];
        }
        return t;
    }
    return *this;
}

const vecto vecto:: operator = (const vecto &v){
    if(this != &v){
        this->n = v.n;
        delete [] data;
        this->data = new double[n];
        for(int i= 0; i<n; i++){
            this->data[i] = v[i];
        }
    }
    
    return *this;
}

double& vecto :: operator [] (int i)const {
    return data[i];
}