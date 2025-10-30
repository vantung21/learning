#include "Linklist.h"

int main(){
    Linklist l;
    l.addfirst(3);
    l.addlast(5);
    l.addfirst(1);
    l.addafter(3, 4);

    cout << "Danh sach: " << l << endl;

    l.removefirst();
    l.removelast();
    cout << "Sau khi xoa dau/cuoi: " << l << endl;

    l.insert(7);
    l.insert(2);
    l.insert(9);
    cout << "Sau khi insert: " << l << endl;

    l.remove(4);
    cout << "Sau khi xoa 4: " << l << endl;

    l.sort(Ascending);
    cout << "Tang dan: " << l << endl;

    l.sort(Descending);
    cout << "Giam dan: " << l << endl;

    return 0;
}