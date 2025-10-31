#include<iostream>
#include<vector>
#include<cstring>
#include<algorithm>

using std::vector;
using std::string;
using std::cin;
using std::cout;
string s1,s2;
inline vector<int> prefix_function(const string &s) {
    int len=s.size();
    vector<int> f(len,0);
    for(int i=1;i<len;i++) {
        if(s[i]==s[f[i-1]]) f[i]=f[i-1]+1;
        else {
            int j=f[i-1];
            while(j>0&&s[i]!=s[j]) j=f[j-1];
            if(s[i]==s[j]) f[i]=j+1;
            else f[i]=0;
        }
    }
    return f;
}
inline vector<int> kmp(const string &s1,const string &s2) {
    string cur=s2+'#'+s1;
    int len=cur.size();
    int n=s2.size();
    vector<int> f=prefix_function(cur);
    vector<int> res;
    for(int i=n+1;i<len;i++) {
        if(f[i]==n) res.push_back(i-2*n);
    }
    return res;
}
int main() {
    cin>>s1>>s2;
    vector<int> ans=kmp(s1,s2);
    for(auto &x:ans) cout<<x<<" ";
    return 0;
}