#include<iostream>
#include<algorithm>
#include<functional>
#include<vector>
#include<stack>

using std::vector;
using std::size_t;
template<typename T,class Cmp=std::less<T>>
class LeftistHeap {
public:
    class Node {
        public:
        T val;
        Node* left;
        Node* right;
        int npl;
        Node(const T& v):val(v),left(nullptr),right(nullptr),npl(0) {}
    };

private:
    Node* root_=nullptr;
    size_t sz_=0;
    Cmp cmp_;

public:
    LeftistHeap()=default;
    ~LeftistHeap() { clear(); }

    bool empty() const { return sz_==0; }
    size_t size() const { return sz_; }
    const T& top() const { return root_->val; }
    T& top() { return root_->val; }

    void merge(LeftistHeap<T,Cmp>& other) {
        if(this==&other) return ;
        root_=merge(root_,other.root_);
        sz_+=other.sz_;
        other.root_=nullptr;
        other.sz_=0;
    }

    void push(const T& x) {
        Node* newNode=new Node(x);
        root_=merge(root_,newNode);
        sz_++;
    }

    void pop() {
        if(!root_) return ;
        Node* L=root_->left;
        Node* R=root_->right;
        delete root_;
        root_=merge(L,R);
        sz_--; 
    }

    void clear() {
        if(!root_) { sz_=0;return ; }
        std::stack<Node*> S;
        Node* cur=root_;
        Node* pre=nullptr;
        while(cur||!S.empty()) {
            if(cur) { S.push(cur);cur=cur->left; }
            else {
                Node* s=S.top();
                if(s->right&&pre!=s->right) cur=s->right;
                else {
                    S.pop();
                    pre=s;
                    delete s;
                }
            }
        }
        root_=nullptr;
        sz_=0;
    }

private:
    static int get_npl(Node* x) { return x?x->npl:-1; } 

    Node* merge(Node* a,Node* b) {
        if(!a) return b;
        if(!b) return a;
        if(cmp_(b->val,a->val)) std::swap(a,b);
        a->right=merge(a->right,b);
        push_up(a);
        return a;
    }

    void push_up(Node* x) {
        if(!x) return ;
        int nplL=get_npl(x->left);
        int nplR=get_npl(x->right);
        if(nplL<nplR) std::swap(x->left,x->right);
        x->npl=get_npl(x->right)+1;
    }
};

int main() {
    LeftistHeap<int> lh1,lh2;
    vector<int> v1,v2;
    v1={3,5,1,7,9};v2={6,4,2,8,10};
    for(int x:v1) lh1.push(x);
    for(int x:v2) lh2.push(x);
    lh1.pop();lh2.pop();
    lh1.merge(lh2);
    while(!lh1.empty()) {
        std::cout<<lh1.top()<<" ";
        lh1.pop();
    }
    return 0;
}