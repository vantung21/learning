

#include <iostream>

using namespace std;

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
        friend ostream& operator << (ostream& out, const Set<T>& s);
};


template <typename T>
Set<T>::Set(int size, T *arr) {
    n = size;
    elements = new T[n];
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
    T *temp = new T[n];
    for (int i = 0; i < n; i++) {
        temp[i] = elements[i];
    }
    delete[] elements; 
    elements = new T[n + 1];
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
    Set<T> result(n + s.n, elements);
    for (int i = 0; i < s.n; i++) {
        result + s.elements[i];         
    }
    return result;
}

template <typename T>
Set<T> Set<T>::operator-(const Set &s) {
    Set<T> result(n, elements);
    for (int i = 0; i < s.n; i++) {
        result - s.elements[i];
    }
    return result;
}

template <typename T>
Set<T> Set<T>::operator*(const Set &s) {
    Set<T> result(0, nullptr); 
    for (int i = 0; i < s.n; i++) {
        if(this->operator()(s.elements[i])) {
            result + s.elements[i]; 
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
        throw std::out_of_range("Index out of range");
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



