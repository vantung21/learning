#include <iostream>
#include <string.h>
#include <iomanip>
using namespace std;

struct HS{
    string name;
    double toan, van;
    double TB;
    string xeploai;
};

istream& operator >> (istream &in, HS &a){
    cout << "Ho ten hoc sinh: ";
    in.ignore();
    getline(in, a.name);
    
    cout<< "diem toan: ";
    in >> a.toan;
    cout << "diem van: ";
    in >> a.van;
    while(a.toan >= 10.0 || a.toan <= 0 || a.van >= 10.0 || a.van <= 0){
        cout << "diem khong hop le! Nhap lai:\n";
        cout<< "diem toan: ";
        in >> a.toan;
        cout << "diem van: ";
        in >> a.van;
    }
    a.TB = (3*a.toan + 2*a.van)/5;
    if(a.TB >= 8.0) a.xeploai = "GIOI";
    else if(a.TB >= 7.0) a.xeploai = "KHA";
    else if(a.TB >= 5.0) a.xeploai = "TRUNG BINH";
    else a.xeploai = "YEU";
    return in;
}

ostream& operator << (ostream &out, HS a){
    out <<"\n" << a.name << endl;
    out << "diem toan: " << a.toan << endl;
    out << "diem van: " << a.van << endl;
    out << "diem trung binh: " << a.TB << endl;
    out << "Xep loai: " << a.xeploai << endl;
    return out;
}

bool ascending(int l, int r){ return l > r;}
bool descending(int l, int r){ return l < r;}
void swap(HS &l, HS &r){
    HS t = l; l=r; r=t;
}
//BubbleSoft
void sortTB(HS lop[], int n, bool (*cmp)(int, int )){
    for(int i=0; i<n-1; i++){
        for(int j = 0; j < n-i-1; j++){
            if(cmp(lop[j].TB, lop[j+1].TB)) swap(lop[j], lop[j+1]);
        }
    }
}

void showListSort(HS lop[], int n, bool (*cmp)(int, int )){
    sortTB(lop, n, cmp);
    cout << setw(20) << "ho ten" << setw(15) <<  "Diem TB" << setw(15) << "Xep loai" << endl;
    for(int i=0; i<n; i++){
        cout << setw(20) << lop[i].name << setw(15) << lop[i].TB << setw(15) << lop[i].xeploai << endl; 
    }
}

int main(){
    int n;
    cout << "nhap so hoc sinh: "; cin >> n;
    HS lop[n];
    for(int i = 0; i< n; i++){
        cout << "Nhap thong tin hoc sinh thu " << i+1 << endl;
        cin >> lop[i];
    }
    for(int i = 0 ; i<n; i++){
        cout << lop[i] ;
    }
    showListSort(lop, n, ascending);

    return 0;
}