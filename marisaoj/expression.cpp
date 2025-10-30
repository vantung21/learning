#include <bits/stdc++.h>
using namespace std;

int main(){
    string S; 
    cin >> S;
    int n = S.size();
    stack<long long> st;
    char dau = '+';
    long long so = 0;
    int front = 0; 
    int end = 0;
    for(int i=0; i<n; i++){
        if(isdigit(S[i])) 
            end++;
        else {
            so = stoll(S.substr(front, end-front+1));
            if(dau == '+'){
                st.push(so);
            }
            else if(dau == '-'){
                st.push(-so);
            }
            else if(dau == '*'){
                long long tmp = st.top(); st.pop();
                st.push(so*tmp);
            }
            else {
                long long tmp = st.top(); st.pop();
                st.push(tmp/so);
            }
            so = 0;
            dau = S[i];
            front = i + 1; 
            end = front;
        }

    }

    so = stoll(S.substr(front, n-1));
    if(dau == '+'){
        st.push(so);
    }
    else if(dau == '-'){
        st.push(-so);
    }
    else if(dau == '*'){
        long long tmp = st.top(); st.pop();
        st.push(so*tmp);
    }
    else {
        long long tmp = st.top(); st.pop();
        st.push(tmp/so);
    }
    long long sum = 0;
    while(!st.empty()){
        sum  += st.top(); st.pop();
    }
    cout << sum << endl;


    return 0;
}