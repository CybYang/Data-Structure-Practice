//线索化二叉树直接在已有的 BinaryTree 上进行修改
#include<bits/stdc++.h>
using namespace std;

template<typename T>
class ThreadedBinaryTree{
public:
    class Node{
    public:
        T val;
        Node* left;
        Node* right;
        bool ltag,rtag;
        explicit Node(const T& v):val(v),left(nullptr),right(nullptr),ltag(false),rtag(false) {}
    };

private:
    Node* root_=nullptr;
    size_t sz_=0;
    bool threaded_=false;

public:
    ThreadedBinaryTree()=default;

    ~ThreadedBinaryTree() { clear(root_);root_=nullptr;sz_=0; }

    bool empty() const { return sz_==0; }

    size_t size() const { return sz_; }

    void insert(const T& x)
    {
        if(!root_) { root_=new Node(x);sz_++;return; }
        Node* cur=root_;Node* fa=nullptr;
        while(cur)
        {
            fa=cur;
            if(x<cur->val) cur=cur->left;
            else if(x>cur->val) cur=cur->right;
            else return;
        }
        if(x<fa->val) fa->left=new Node(x);
        else fa->right=new Node(x);
        sz_++;
    }

    bool Find(const T& x) const
    {
        Node* cur=root_;
        while(cur)
        {
            if(x==cur->val) return true;
            cur=(x<cur->val)?cur->left:cur->right;
        }
        return false;
    }

    void inorder(vector<T>& res) const
    {
        
        if(!root_) return ;
        auto goleft=[&](Node* x)
        {
            while(x&&!x->ltag&&x->left) x=x->left;
            return x;
        };
        Node* cur=goleft(root_);
        while(cur)
        {
            res.push_back(cur->val);
            if(cur->rtag) cur=cur->right;
            else cur=goleft(cur->right);
        }
    }

    void threadedinorder()
    {
        if(threaded_) return ;
        Node* pre=nullptr;
        function<void(Node*)> dfs=[&](Node* cur)
        {
            if(!cur) return ;
            dfs(cur->left);
            if(!cur->left)
            {
                cur->ltag=true;
                cur->left=pre;
            }
            if(pre&&!pre->right)
            {
                pre->rtag=true;
                pre->right=cur;
            }
            pre=cur;
            dfs(cur->right);
        };
        dfs(root_);
        if(pre&&!pre->right)
        {
            pre->rtag=true;
            pre->right=nullptr;
        }
        threaded_=true;
    }

private:
    void clear(Node* n)
    {
        if(!n) return ;
        if(!n->ltag) clear(n->left);
        if(!n->rtag) clear(n->right);
        delete n;
    }
};
int main() 
{
    ThreadedBinaryTree<int> bt;
    for (int v:{5,3,8,1,4,7,9,2,6}) bt.insert(v);
    vector<int> pre,in,post;
    bt.threadedinorder();
    bt.inorder(in);

    auto print=[](string name,const vector<int>& a)
    {
        cout<<name<<": "<<endl;
        for(int x:a) cout<<x<<' ';
        cout<<'\n';
    };
    print("in ", in);
    return 0;
}
