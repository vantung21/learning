#include<iostream>

using namespace std;

int ucln(int a, int b){
    if(b!= 0) return ucln(b, a%b);
    return a;
}
int main(){
    int a,b;
    cin>> a>> b;
    int c = ucln(a,b);
    cout<< a/c<<" "<<b/c;

    
    return 0;
}