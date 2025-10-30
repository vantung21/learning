#include<iostream>

using namespace std;

class MATRIX{
    private:
        int n;
        int **data;
    public:
        MATRIX(int n = 2);
        ~MATRIX();
        MATRIX(const MATRIX &m);
        MATRIX operator + (const MATRIX &m);
        MATRIX operator - (const MATRIX &m);
        MATRIX operator * (const MATRIX &m);
        friend istream& operator >> (istream& in, MATRIX &m);
        friend ostream& operator << (ostream& out, const MATRIX &m);
        MATRIX& operator = (const MATRIX &m);
        int operator ()(int i, int j)const; // truy xuat phan tuw hang i cot j
};

MATRIX :: MATRIX(int n): n(n) {
    data = new int*[n];
    for(int i = 0; i<n; i++){
        data[i] = new int[n];
    }
}
MATRIX :: MATRIX(const MATRIX &m){
    this->n = m.n;
    data = new int*[n];
    for(int i = 0; i<n; i++){
        data[i] = new int[n];
    }
    for(int i = 0; i<n; i++){
        for(int j=0; j<n; j++){
            data[i][j] = m.data[i][j];
        }
    }
}

MATRIX :: ~MATRIX(){
    for(int i = 0; i< n; i++){
        delete [] data[i];
    }
    delete [] data;
}

istream& operator >> (istream& in, MATRIX &m){
    for(int i =0; i<m.n; i++){
        for(int j=0; j<m.n; j++){
            in >> m.data[i][j];
        }
    }
    return in;
}
ostream& operator << (ostream& out, const MATRIX &m){
    for(int i =0; i<m.n; i++){
        for(int j=0; j<m.n; j++){
            out << m.data[i][j] << " ";
        }
        out << endl;
    }
    return out;
}


MATRIX MATRIX :: operator + (const MATRIX &m){
    if(n == m.n){
        MATRIX t(n);
        for(int i =0; i<n; i++){
            for(int j=0; j<n; j++){
            t.data[i][j] = this->data[i][j] + m.data[i][j];
            }
        }
        return t;
    }  
    return *this;  
}
MATRIX MATRIX :: operator - (const MATRIX &m){
    if(n == m.n){
        MATRIX t(n);
        for(int i =0; i<n; i++){
            for(int j=0; j<n; j++){
            t.data[i][j] = this->data[i][j] - m.data[i][j];
            }
        }
        return t;
    }  
    return *this;
}

MATRIX MATRIX :: operator * (const MATRIX &m){
    if(n == m.n){
        MATRIX t(n);
        for(int i =0; i<n; i++){
            for(int j=0; j<n; j++){
                t.data[i][j] = 0;
                for(int k =0; k<n; k++){
                    t.data[i][j] += this->data[i][k]*m.data[k][j];    
                }
            }
        }
        return t;
    }  
    return *this;
}

MATRIX& MATRIX :: operator = (const MATRIX &m){
    if(this != &m){
        this->n = m.n;
        for(int i = 0; i<n; i++){
            delete [] data[i];
        }
        delete [] data;

        data = new int*[n];
        for(int i = 0; i<n; i++){
            data[i] = new int[n];
        }

        for(int i =0 ; i< n; i++){
            for(int j = 0; j< n; j++){
                this->data[i][j] = m.data[i][j]; 
            }
        }
    }
    return *this;
}

int MATRIX :: operator ()(int i, int j)const{
    return data[i-1][j-1];
}

int main(){
    MATRIX A(3), B(3);
    cin >> A>> B;
    cout << "matran A: \n";
    cout << A ;
    cout << "matran B: \n";
    cout << B;

    MATRIX C = A + B;
    cout << "matran C: \n";
    cout << C;

    cout << "phan tu hang 1 cot 2 cua ma tran A:\n";
    cout << A(1,2) << endl;

    MATRIX D = A*B;
    cout << "matran D: \n";
    cout << D;

    return 0;
}