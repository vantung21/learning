#include<bits/stdc++.h>
using namespace std;




int main(){
    string s1, s2;
    cin >> s1 >> s2;
    int cnt = 1;
    for(int i =1; i<s1.size(); i++){
        if(s1[i] == s1[i-1]) cnt++;
        else{
            cout << cnt << s1[i-1];
            cnt = 1;
        }
    }
    cout << cnt << s1[s1.size()-1] << endl;


    cnt = 0;
    int m = s2.size();
    string res = "";
    for(int i =0 ; i<m; i++){
        while(i <m && isdigit(s2[i])){
            cnt = cnt*10 + s2[i] - '0';
            i++;
        }
        if(i < m && isalpha(s2[i])){
            res += string(cnt, s2[i]);
            cnt = 0;
        }
    }
    cout << res << endl;

    return 0;
}