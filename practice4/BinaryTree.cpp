#include<bits/stdc++.h>
using namespace std;

template<typename T>
class BinaryTree{
public:
    class Node{
    public:
        T val;
        Node* left;
        Node* right;
        explicit Node(const T& v):val(v),left(nullptr),right(nullptr) {}
    };

private:
    Node* root_=nullptr;
    size_t sz_=0;

public:
    BinaryTree()=default;

    ~BinaryTree() { clear(); }

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

    void preorder(vector<T>& res) const
    {
        if(!root_) return ;
        stack<Node*> S;S.push(root_);
        while(!S.empty())
        {
            Node* cur=S.top();S.pop();
            res.push_back(cur->val);
            if(cur->right) S.push(cur->right);
            if(cur->left) S.push(cur->left);
        }
    }

    void inorder(vector<T>& res) const
    {
        if(!root_) return ;
        stack<Node*> S;
        Node* cur=root_;
        while(cur||!S.empty())
        {
            while(cur) { S.push(cur);cur=cur->left; }
            cur=S.top();S.pop();
            res.push_back(cur->val);
            cur=cur->right;
        }
    }

    void postorder(vector<T>& res) const
    {
        if(!root_) return ;
        stack<Node*> S;
        Node* cur=root_;
        Node* pre=nullptr;
        while(cur||!S.empty())
        {
            if(cur) { S.push(cur);cur=cur->left; }
            else
            {
                Node* s=S.top();
                if(s->right&&pre!=s->right) cur=s->right;
                else
                {
                    res.push_back(s->val);
                    pre=s;
                    S.pop();
                }
            }
        }
    }

private:
    void clear()
    {
        Node* cur=root_,*pre=nullptr;
        stack<Node*>S;
        while(cur||!S.empty())
        {
            if(cur) { S.push(cur);cur=cur->left; }
            else
            {
                Node* s=S.top();
                if(s->right&&pre!=s->right) cur=s->right;
                else
                {
                    S.pop();
                    pre=s;
                    delete s;
                }
            }
        }
        root_=nullptr;
        sz_=0;
    }
};
int main() 
{
    BinaryTree<int> bt;
    for (int v:{5,3,8,1,4,7,9,2,6}) bt.insert(v);

    vector<int> pre,in,post;
    bt.preorder(pre);
    bt.inorder(in);
    bt.postorder(post);

    auto print=[](string name,const vector<int>& a)
    {
        cout<<name<<": "<<endl;
        for(int x:a) cout<<x<<' ';
        cout<<'\n';
    };
    print("pre", pre);
    print("in ", in);
    print("post", post);
    return 0;
}
