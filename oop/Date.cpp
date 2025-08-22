#include <iostream>
using namespace std;

struct Date {
    int d,m,y;
};

bool namnhuan (int y){
    return (y%400 == 0 || (y%4 == 0 && y%100 != 0));
}

int songaytrongthang(Date x){
    int songay[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if(x.m == 2 && namnhuan(x.y)) return 29;
    return songay[x.m];
}

istream &operator >> (istream &in, Date &x){
    while(1){
        in >> x.d >> x.m >> x.y;
        if(x.y > 0 && x.m > 0 && x.m <=12 && x.d > 0 && x.d <= songaytrongthang(x)){
            break; // hop le
        }
        cout << "ngay, thang, nam khong hop le!" << endl << "nhap lai: ";
    }
    return in;
}
ostream &operator << (ostream &out, Date x){
    out << x.d << "/" << x.m << "/" << x.y;
    return out; 
}


// tien to
Date operator ++ (Date &x){
    x.d++;
    if(x.d > songaytrongthang(x)){
        x.d = 1; x.m++;
        if(x.m > 12){
            x.m = 1; x.y++;
        }
    }
    return x;
}

Date operator -- (Date &x){
    x.d--;
    if(x.d < 1 && x.m > 1){
        x.m--;
        x.d = songaytrongthang(x);
    }
    else if(x.d < 1 && x.m == 1){
        x.y--;
        x.d = 31;
        x.m = 12;
    }
    return x;
}

// hau to
Date operator ++ (Date &x, int){
    Date t = x;
    ++x;
    return t;
}

Date operator -- (Date &x, int){
    Date t = x;
    --x; 
    return t;
}

int main(){
    Date a;
    cout << "Nhap ngay hom nay: "; cin >> a;
    cout << "Ngay vua nhap la: "<< a << endl;
    cout <<" Ngay hom qua la: " << --a << endl;
    ++a;
    cout << " Ngay mai la: " << ++a << endl;

    return 0;
}