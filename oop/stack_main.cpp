#include "stack.hpp"

int main(){
    stack st(8);
    int n;
    cout << "nhap so can doi: ";
    cin >> n;
    while(n){
        st.push(n%16);
        n /=16;
    }

    stack s1(st);
    s1.showstack();


    char s[] = "0123456789ABCDEF";
    while(!st.isEmpty()){
        cout << s[st.pop()];
    }
    cout << endl;

    


    return 0;
}