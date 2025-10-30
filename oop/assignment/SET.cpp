#include "SET.h"

SET :: SET(int size){
    this->size = size;
    n = 0; data = new int[size];
}
SET :: SET(int arr[], int len, int size ){
    this->size = size;
    n =0;
    data = new int[size];
    for(int i = 0 ; i< len; i++){
        if(!(*this)(arr[i])) data[n++] = arr[i];
    }
}

SET :: SET(const SET &s){
    this->size = s.size;
    n = s.n;
    data = new int[size];
    for(int i = 0; i<n; i++){
        data[i] = s.data[i];
    }
}

SET SET :: operator + (int a) const {
    SET t(*this);
    if(!t(a) && t.n <size){
        t.data[t.n++] = a;
    }
    return t;
}
SET SET :: operator - (int a)const {
    SET t(*this);
    for(int i = 0; i<t.n; i++){
        if(t.data[i] == a){
            for(int j =i; j<t.n-1; j++){
                t.data[j] = t.data[j+1];
            }
            t.n--;
            break;
        }
    }
    return t;
}
SET SET :: operator + (const SET& s) const{
    SET t(*this);
    for(int i =0; i<s.n; i++){
        if(!t(s.data[i]) && t.n < t.size){
            t.data[t.n++] = s.data[i];
        }
    }
    return t;
}
SET SET :: operator - (const SET& s) const{
    SET t(*this);
    for(int i = 0; i<s.n; i++){
        t = t-s.data[i];
    }
    return t;
}
SET SET :: operator * (const SET& s) const{
    SET t(size);
    for(int i =0; i<n ; i++){
        if(s(data[i])) t.data[t.n++] = data[i]; 
    }
    return t;
}

bool SET :: operator()(int a) const{
    for(int i = 0; i<n; i++){
        if(data[i] == a) return true;
    }
    return false;
}

int& SET :: operator [](int idx){
    return data[idx-1];
}
SET& SET :: operator = (const SET& s){
    if(this != &s){
        delete[] data;
        size = s.size;
        n = s.n;
        data = new int[size];
        for(int i=0; i<s.n; i++){
            data[i] = s.data[i];
        }
    }
    return *this;
}

ostream& operator << (ostream& out, const SET& s){
    out << "{ ";
    for(int i = 0; i<s.n-1 ; i++){
        out << s.data[i] << ", ";
    }
    out << s.data[s.n-1]<< " }";
    return out;
}