#include <iostream>

#define MAX_SIZE 100

using namespace std;

template <typename T> class Set;

template <typename T>
ostream& operator<<(ostream& out, const Set<T>& s);


template <typename T>
class Set{
    private:
        int n; //size
        T *elements; //array of elements
    public:
        Set(int size , T *arr);
        ~Set();
        Set(const Set &s);
        void operator + (T x);
        void operator - (T x);
        Set<T> operator + (const Set &s);
        Set<T> operator - (const Set &s);
        Set<T> operator * (const Set &s);
        bool operator ()(T x);
        T& operator[] (int idx);
        friend ostream& operator << <>(ostream& out, const Set<T>& s);
};


template <typename T>
Set<T>::Set(int size, T *arr) {
    if(size > MAX_SIZE) {
        throw "vuot qua so luong toi da";
    }
    n = size;
    elements = new T[n];
    if(elements == NULL) {
        throw "cap phat khong thanh cong";
    }
    for (int i = 0; i < n; i++) {
        elements[i] = arr[i];
    }
}

template <typename T>
Set<T>::~Set() {
    delete[] elements;
}


template <typename T>
Set<T>::Set(const Set &s) {
    n = s.n;
    elements = new T[n];
    if(elements == NULL) {
        throw "cap phat khong thanh cong";
    }
    for (int i = 0; i < n; i++) {
        elements[i] = s.elements[i];
    }
}

template <typename T>
void Set<T>::operator+(T x) {
    for (int i = 0; i < n; i++) {
        if (elements[i] == x) {
            return; 
        }
    }
    if(n >= MAX_SIZE) {
        throw "vuot qua so luong toi da , khong the them phan tu moi";
    }
    T *temp = new T[n];
    if(temp == NULL) {
        throw "cap phat khong thanh cong";
    }
    for (int i = 0; i < n; i++) {
        temp[i] = elements[i];
    }
    delete[] elements; 
    elements = new T[n + 1];
    if(elements == NULL) {
        throw "cap phat khong thanh cong";
    }
    for (int i = 0; i < n; i++) {
        elements[i] = temp[i];
    }
    elements[n] = x;
    n++;
}    

template <typename T>
void Set<T>::operator-(T x) {
    for (int i = 0; i < n; i++) {
        if (elements[i] == x) {
            // Element found, remove it
            for (int j = i; j < n - 1; j++) {
                elements[j] = elements[j + 1];
            }
            n--;
            return;
        }
    }
}

template <typename T>
Set<T> Set<T>::operator+(const Set &s) {
    Set<T> result(n, elements);
    for (int i = 0; i < s.n; i++) {
        try {
            result + s.elements[i];         
        } catch (const char* e) {
            cout << e << endl;
        };    
    }
    return result;
}

template <typename T>
Set<T> Set<T>::operator-(const Set &s) {
    Set<T> result(n, elements);
    for (int i = 0; i < s.n; i++) {
        try {
            result - s.elements[i];
        } catch (const char* e) {
            cout << e << endl;
        };
    }
    return result;
}

template <typename T>
Set<T> Set<T>::operator*(const Set &s) {
    Set<T> result(0, nullptr); 
    for (int i = 0; i < s.n; i++) {
        if(this->operator()(s.elements[i])) {
            try {
                result + s.elements[i]; 
            } catch (string &e) {
                cout << e << endl;
            };
        }
    }
    return result;
}

template <typename T>
bool Set<T>::operator()(T x) {
    for (int i = 0; i < n; i++) {
        if (elements[i] == x) {
            return true;
        }
    }
    return false;
}

template <typename T>
T& Set<T>::operator[](int idx) {
    if (idx < 0 || idx >= n) {
        throw "phan tu khong hop le";
    }
    return elements[idx];
}

template <typename T>
ostream& operator<<(ostream& out, const Set<T>& s) {
    out << "{ ";
    for (int i = 0; i < s.n; i++) {         
        out << s.elements[i];
        if (i < s.n - 1) {
            out << ", ";
        }
    }
    out << " }";
    return out;
}


int main(){
    try {
        int arrA[] = {1, 2, 3};
        int arrB[] = {3, 4, 5};

        Set<int> A(3, arrA);
        Set<int> B(3, arrB);

        cout << "Tap hop A: " << A << endl;
        cout << "Tap hop B: " << B << endl;

        cout << "Hop A + B: " << (A + B) << endl;
        cout << "Giao A * B: " << (A * B) << endl;
        cout << "Hieu A - B: " << (A - B) << endl;

        // thu them phan tu moi
        cout << "\nThem phan tu 6 vao A:\n";
        A + 6;
        cout << "A sau khi them: " << A << endl;

        // thu them phan tu trung
        cout << "\nThem phan tu trung 3 vao A:\n";
        A + 3;

    } catch (const char* e) {
        cout << "Ngoai le: " << e << endl;
    }

    try {
        int arrC[] = {10, 20, 30};
        Set<int> C(3, arrC);

        cout << "\nTap hop C: " << C << endl;
        cout << "Phan tu thu 1 cua C: " << C[1] << endl;
        cout << "Truy cap sai chi so 10:\n";
        cout << C[10] << endl; // lỗi

    } catch (const char* e) {
        cout << "Ngoai le: " << e << endl;
    }

    return 0;
}

