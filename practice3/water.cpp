#include<bits/stdc++.h>
using namespace std;
int A,B,C;
struct Step{ string opt;int a,b; };
inline int GCD(int x,int y)
{
    if(A<B) swap(A,B);
    while(y)
    {
        int tmp=x%y;
        x=y;
        y=tmp;
    }
    return x;
}
vector<Step> simulate1(int A,int B,int C)
{
    vector<Step>ops;
    int a=0,b=0;
    if(C==0) return ops;
    while(a!=C&&b!=C)
    {
        if(a==0) { a=A;ops.push_back({"Fill A",a,b}); }
        else if(b==B) { b=0;ops.push_back({"Empty B",a,b}); }
        else { int t=min(a,B-b);a-=t;b+=t;ops.push_back({"Pour A->B ("+to_string(t)+")",a,b}); }
    }
    return ops;
}
vector<Step> simulate2(int A,int B,int C)
{
    vector<Step>ops;
    int a=0,b=0;
    if(C==0) return ops;
    while(a!=C&&b!=C)
    {
        if(b==0) { b=B;ops.push_back({"Fill B",a,b}); }
        else if(a==A) { a=0;ops.push_back({"Empty A",a,b}); }
        else { int t=min(b,A-a);a+=t;b-=t;ops.push_back({"Pour B->A (" + to_string(t) + ")",a,b}); }
    }
    return ops;
}
int main()
{
    cin>>A>>B>>C;
    int g=GCD(A,B);
    if(C%g!=0) { puts("No");return 0; }
    puts("Yes");
    auto res1=simulate1(A,B,C);
    auto res2=simulate2(A,B,C);
    const auto& ans=(res1.size()<res2.size())?res1:res2;
    for(const auto& x:ans)
        cout<<left<<setw(14)<<x.opt<<" -> [A="<<x.a<<", B="<<x.b<<"]\n";
    return 0;
}