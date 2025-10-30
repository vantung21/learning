#include<bits/stdc++.h>
using namespace std;

bool namnhuan(long long y){
    return ((y%4==0 &&y%100 !=0) || y%400 == 0);
}

int main(){
    // 146097
    int monthdays[] = {-1, 31, 28, 31, 30, 31, 30, 31, 31,30, 31, 30, 31};
    long long x, d, m ,y;
    cin >> x >> d >> m >> y;
    y += 400*(x/146097);
    x%=146097;
    for(int i = 0; i<x; i++){
        d++;
        if(m == 2){
            if(namnhuan(y)){
                if(d>29){
                    d = 1;
                    m++;
                }
            }
            else{
                if(d >28){
                    d = 1;
                    m++;
                }
            }
        }
        else{
            if(d > monthdays[m]){
                d = 1; m++;
                if(m >= 13){
                    m = 1; y++;
                }
            }
        }
    }
    cout << d << " "<< m << " " << y << endl;
    



    return 0;
}