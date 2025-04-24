#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
int main(){
    string s1,s2,s3;
    cin>>s1>>s2;
    reverse(s1.begin(),s1.end());
    reverse(s2.begin(),s2.end());
    s1.length()>s2.length()?s3=s1:s3=s2;
    int i=0,d=0;
    while(i<s1.length() && i<s2.length()){
        s3[i]=(s1[i]-48+s2[i]-48+d)%10+48;
        d= (s1[i]-48+s2[i]-48+d)/10;
        i++;
    }
    for(int j=i;j<s3.length(); j++){
        int n= (s3[j]-48+d)/10;
        s3[j]=(s3[j]-48+d)%10+48;
        d= n;
    }
    reverse(s3.begin(),s3.end());
    cout<<s3;
}