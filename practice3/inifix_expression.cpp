#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int prec(char op)
{
    if(op=='+'||op=='-') return 1;
    if(op=='*'||op=='/') return 2;
    if(op=='^') return 3;
    return -1;
}
bool right_assoc(char op){ return op=='^'; }
ll apply(ll a ,ll b,char op)
{
    switch(op)
    {
        case '+': return a+b;
        case '-': return a-b;
        case '*': return a*b;
        case '/': 
        {
            if(b==0) throw runtime_error("division by zero");
            return a/b;
        }
        case '^':
        {
            if(b<0) throw runtime_error("negative exponent");
            ll res=1,base=a;ll k=b;
            while(k)
            {
                if(k&1) res*=base;
                base*=base;
                k>>=1;
            }
            return res;
        }
    }
    throw runtime_error("unknown operator");
}
void settle_top(stack<ll>& val,stack<char>& opt)
{
    if(opt.empty()||val.size()<2) throw runtime_error("malformed");
    char op=opt.top();opt.pop();
    ll b=val.top();val.pop();
    ll a=val.top();val.pop();
    val.push(apply(a,b,op));
}
ll calc(string s)
{
    stack<ll>val;
    stack<char>opt;
    auto isop=[](char c) { return c=='+'||c=='-'||c=='*'||c=='/'||c=='^'; };
    bool unary=true;
    for(size_t i=0;i<s.size();)
    {
        if(isspace((unsigned char)s[i])) { i++;continue; }
        if(isdigit((unsigned char)s[i]))
        {
            ll num=0;
            while(i<s.size()&&isdigit((unsigned char)s[i]))
            {
                num=num*10+s[i]-'0';
                i++;
            }
            val.push(num);
            unary=false;
        }
        else if(s[i]=='(') { opt.push('(');i++;unary=true; }
        else if(s[i]==')')
        {
            while(!opt.empty()&&opt.top()!='(') settle_top(val,opt);
            if(opt.empty()) throw runtime_error("mismatched parentheses");
            opt.pop();i++;unary=false;
        }
        else if(isop(s[i]))
        {
            char cur=s[i];
            if((cur=='+'||cur=='-')&&unary) val.push(0);
            while(!opt.empty()&&opt.top()!='('&&(prec(opt.top())>prec(cur)||(prec(opt.top())==prec(cur)&&!right_assoc(cur)))) { settle_top(val,opt); }
            opt.push(cur);
            i++;
            unary=true;
        }
        else { throw runtime_error(string("invalid char: ")+s[i]); }
    }
    while(!opt.empty())
    {
        if(opt.top()=='(') throw runtime_error("mismatched parentheses");
        settle_top(val,opt);
    }
    if(val.size()!=1) throw runtime_error("malformed");
    return val.top();
}
int main()
{
    string expr;
    getline(cin,expr);
    try{ cout<<calc(expr)<<endl; }
    catch(const exception& e) { cerr<<"Error:"<<e.what()<<endl; }
    return 0;
}
/*
(2 + 3) * 4 - 5^2 + -6
*/