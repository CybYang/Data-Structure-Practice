#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

class Huffman{
public:
    struct Node
    {
        ll cnt;
        char ch;
        Node *left,*right;
        Node(ll cnt,char ch='\0',Node* left=nullptr,Node* right=nullptr)
            :cnt(cnt),ch(ch),left(left),right(right) {}
    };
    Huffman():root_(nullptr) {}
    ~Huffman() { clear(root_); }

    void build(const vector<pair<char,ll>>& v)
    {
        priority_queue<Node*,vector<Node*>,cmp>Q;
        for(auto &x:v) Q.push(new Node(x.second,x.first));
        if(Q.empty()) { root_=nullptr;return; }
        if(Q.size()==1) { root_=Q.top();return; }
        while(Q.size()>1)
        {
            Node* x=Q.top();Q.pop();
            Node* y=Q.top();Q.pop();
            Q.push(new Node((*x).cnt+(*y).cnt,'\0',x,y));
        }
        root_=Q.top();
    }

    void cal(const string& str)
    {
        unordered_map<char,ll>mp;
        for(char c:str) mp[c]++;
        vector<pair<char,ll>>v;
        v.reserve(mp.size());
        for(auto &x:mp) v.emplace_back(x.first,x.second);
        build(v);
    }

    unordered_map<char,string> codes() const
    {
        unordered_map<char,string>mp;
        if(!root_) return mp;
        string path;
        dfs(root_,path,mp);
        return mp;
    }

    string encode(const string &str) const
    {
        unordered_map<char,string>mp=codes();
        string res;
        res.reserve(str.size()*2);
        for(char c:str)
        {
            auto it=mp.find(c);
            if(it==mp.end()) throw runtime_error("encode:char not found");
            res+=it->second;
        }
        return res;
    }

    string decode(const string &str) const
    {
        if(!root_) return "";
        if(!root_->left&&!root_->right) return string((int)str.size(),root_->ch);
        string res;
        Node* cur=root_;
        for(char c:str)
        {
            if(c=='0') cur=cur->left;
            else if(c=='1') cur=cur->right;
            else throw runtime_error("decode:invalid code");
            if(!cur->left&&!cur->right)
            {
                res.push_back(cur->ch);
                cur=root_;
            }
        }
        return res;
    }

    ll WPL() const { return wpl(root_,0); }
private:
    Node* root_;
    struct cmp
    {
        bool operator()(const Node*a,const Node*b) const { return (*a).cnt>(*b).cnt; }
    };
    void clear(Node* x)
    {
        if(!x) return ;
        clear(x->left);
        clear(x->right);
        delete x;
    }
    static void dfs(const Node* x,string &path,unordered_map<char,string> &mp) 
    {
        if(!x) return;
        if(!x->left&&!x->right)
        {
            mp[x->ch]=path.empty()?"0":path;
            return ;
        }
        path.push_back('0');dfs(x->left,path,mp);path.pop_back();
        path.push_back('1');dfs(x->right,path,mp);path.pop_back();
    }
    static ll wpl(const Node* x,int dep)
    {
        if(!x) return 0;
        if(!x->left&&!x->right) return ll(dep)*(*x).cnt;
        return wpl(x->left,dep+1)+wpl(x->right,dep+1);
    }
};
int main()
{
    string str="beep boop been beer bear pear";
    Huffman H;
    H.cal(str);
    auto mp=H.codes();
    string res1=H.encode(str);
    string res2=H.decode(res1);
    cout<<"Original: "<<str<<"\n";
    cout<<"Encoded : "<<res1<<"\n";
    cout<<"Decoded : "<<res2<<"\n";
    cout<<"OK? "<<(str==res2?"YES":"NO")<<"\n";
    cout<<"WPL2 = "<<H.WPL()<<"\n";
    return 0;
}