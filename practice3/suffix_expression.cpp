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
            ll res=1,base=a; ll k=b;
            while(k)
            {
                if(k&1) res*=base;
                k>>=1;
                if(k) base*=base;
            }
            return res;
        }
    }
    throw runtime_error("unknown operator");
}
vector<string> infix_to_rpn(const string& s)
{
    vector<string> rpn;
    stack<char> opt;
    auto isop=[](char c){ return c=='+'||c=='-'||c=='*'||c=='/'||c=='^'; };
    bool unary=true;
    for(size_t i=0;i<s.size();)
    {
        if(isspace((unsigned char)s[i])) { i++;continue; }
        if(isdigit((unsigned char)s[i]))
        {
            ll num=0;
            while(i<s.size()&&isdigit((unsigned char)s[i]))
            {
                num=num*10+(s[i]-'0');
                ++i;
            }
            rpn.push_back(to_string(num));
            unary=false;
        }
        else if(s[i]=='(')
        {
            opt.push('(');
            ++i;
            unary=true;
        }
        else if(s[i]==')')
        {
            while(!opt.empty() && opt.top()!='(')
            {
                rpn.push_back(string(1,opt.top()));
                opt.pop();
            }
            if(opt.empty()) throw runtime_error("mismatched parentheses");
            opt.pop();
            i++;
            unary=false;
        }
        else if(isop(s[i]))
        {
            char cur=s[i];
            if((cur=='+'||cur=='-') && unary) rpn.push_back("0");
            while(!opt.empty()&&opt.top()!='('&&(prec(opt.top())>prec(cur)||(prec(opt.top())==prec(cur) && !right_assoc(cur))))
            {
                rpn.push_back(string(1,opt.top()));
                opt.pop();
            }
            opt.push(cur);
            i++;
            unary=true;
        }
        else{ throw runtime_error(string("invalid char: ")+s[i]); }
    }
    while(!opt.empty())
    {
        if(opt.top()=='(') throw runtime_error("mismatched parentheses");
        rpn.push_back(string(1,opt.top()));
        opt.pop();
    }
    return rpn;
}
ll eval_rpn(const vector<string>& rpn)
{
    stack<ll> st;
    auto isop_token=[](const string& t){ return t.size()==1 && (t[0]=='+'||t[0]=='-'||t[0]=='*'||t[0]=='/'||t[0]=='^'); };
    for(const auto& tok:rpn)
    {
        if(isop_token(tok))
        {
            if(st.size()<2) throw runtime_error("malformed RPN");
            ll b=st.top(); st.pop();
            ll a=st.top(); st.pop();
            st.push(apply(a,b,tok[0]));
        }
        else{ st.push(stoll(tok)); }
    }
    if(st.size()!=1) throw runtime_error("malformed RPN");
    return st.top();
}
int main()
{
    string expr;
    getline(cin,expr);
    try
    {
        vector<string> rpn = infix_to_rpn(expr);
        cout<<eval_rpn(rpn)<<endl;
    }
    catch(const exception& e) { cerr<<"Error:"<<e.what()<<"\n"; }
    return 0;
}
/*
(2 + 3) * 4 - 5^2 + (-6)
*/
