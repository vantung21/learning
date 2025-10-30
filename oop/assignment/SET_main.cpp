#include "SET.h"

int main(){
    int a[] = {1, 2, 3, 4, 5};
    SET s1(a, 5, 20);
    SET s2;
    s2 = s1 + 6;
    s2 = s2 - 3;

    cout << "Tap hop s1: " << s1 << endl;
    cout << "Tap hop s2: " << s2 << endl;

    SET s3 = s1 + s2;
    cout << "Hop s1 va s2: " << s3 << endl;

    SET s4 = s1 - s2;
    cout << "Hieu s1 - s2: " << s4 << endl;

    SET s5 = s1 * s2;
    cout << "Giao s1 va s2: " << s5 << endl;

    cout << "Phan tu 2 co thuoc s1 khong? " << (s1(2) ? "Co" : "Khong") << endl;
    cout << "Phan tu thu 1 cua s1: " << s1[1] << endl;

   
    return 0;
}